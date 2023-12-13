##
## CMakeLists: R-Type / Server
##

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# project name
project(r-type_server)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/..)

# option to build tests
option(RTYPE_BUILD_TESTS "Build the tests" OFF)

# include directories
include_directories(include/)

# Warning flags
set(GCC_WARNING_FLAGS
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
    -Wlogical-op -Wnull-dereference -Wuseless-cast -Wno-pragmas)

set(CLANG_WARNING_FLAGS
    -Weverything
    -Wno-c++20-compat
    -Wno-c++98-c++11-compat-binary-literal
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c99-extensions
    -Wno-disabled-macro-expansion
    -Wno-documentation-unknown-command
    -Wno-exit-time-destructors
    -Wno-missing-prototypes
    -Wno-global-constructors
    -Wno-implicit-int-float-conversion
    -Wno-return-std-move
    -Wno-return-type-c-linkage
    -Wno-signed-enum-bitfield
    -Wno-weak-vtables)

if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 13.0.0)
    set(CLANG_WARNING_FLAGS ${CLANG_WARNING_FLAGS} -Wno-return-std-move-in-c++11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -std=c++20")

set(WARNING_FLAGS
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -pedantic
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Wno-covered-switch-default
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wdouble-promotion
    -Wformat=2
    -Weffc++
    -Wno-padded
    -Wno-ctad-maybe-unsupported)

if (RTYPE_BUILD_TESTS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# set colors for the messages because why not ?
if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()

# set different flags
set(CMAKE_BUILD_TYPE
    ${CMAKE_BUILD_TYPE}
    CACHE
      STRING
      "Choose the type of build, options are: None Debug"
      FORCE)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Clang-tidy
if(USE_CLANG_TIDY)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
      if(DEFINED RTYPE_CLANG_TIDY_FLAGS)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
          "${RTYPE_BUILD_TESTS_CLANG_TIDY_FLAGS}")
    else()
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
    message("-- Found clang-tidy: ${CLANG_TIDY_EXE}")
  else()
    message("-- Failed to find clang-tidy")
  endif()
endif()

# set warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(WARNING_FLAGS ${WARNING_FLAGS} ${CLANG_WARNING_FLAGS})
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(WARNING_FLAGS ${WARNING_FLAGS} ${GCC_WARNING_FLAGS})
else()
  error("${CMAKE_CXX_COMPILER_ID}: Unsupported compiler.")
endif()

message("Warning flags: ${Cyan} ${WARNING_FLAGS}${ColourReset}")

# if shared libraries need to have template files
add_library(rtype-server-interface INTERFACE)

# link the library
set_property(TARGET rtype-server-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-server-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-server-interface INTERFACE
    asio::asio
    )

# add library with all of the source file, execpt for the main
add_library(
    rtype-server-core
    SHARED
    src/Manager.cpp
    src/utils.cpp
    src/config/ArgsParser.cpp
    src/clients/Player.cpp
    src/clients/PlayersManager.cpp
    src/clients/MessageQueue.cpp
    src/clients/ThreadPool.cpp
    src/GameLogic/GameLogic.cpp
)

target_compile_features(rtype-server-core PRIVATE cxx_std_20)
target_compile_options(rtype-server-core PRIVATE ${WARNING_FLAGS})
target_include_directories(rtype-server-core PUBLIC include ../RType-Utils/include/ ../GameEngine/ECS/include ../GameEngine/Physics/include)
set_property(TARGET rtype-server-core PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-server-core PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-server-core PRIVATE
    rtype-server-interface
    r-type-utils
    asio::asio # link asio library to core
    )

message("${BoldWhite}Finished loading rtype-core${ColourReset}")

# add the executable with the main
add_executable(
    r-type_server
    src/main.cpp
    )

# link the libraries to executable
target_link_libraries(
    r-type_server PRIVATE
    rtype-server-core
    rtype-server-interface
    )
target_compile_features(r-type_server PRIVATE cxx_std_20)
target_compile_options(r-type_server PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type_server PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED ON)
