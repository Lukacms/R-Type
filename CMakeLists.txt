cmake_minimum_required(VERSION 3.6)

project(r-type)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)
set(VERSION_PATCH 1)

# executables will be at the root of the folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# options of the project
option(RTYPE_BUILD_TESTS "Build the tests" OFF)
option(RTYPE_BUILD_BENCHMARKS "Build benchmarks" OFF)

# fetch asio library which is used by both client and server
message("Loading Asio library")

option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
    ASIO_CPM_FETCHCONTENT_COMPAT
    "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
    ON
)
# option(ASIO_TAG "tag instead of main branch" asio-1-28-2)

# Download this repository
include(FetchContent)

FetchContent_Declare(
    asiocmake
    GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
    GIT_TAG        "main"
    SYSTEM
)

FetchContent_MakeAvailable(asiocmake)

message("Finished loading Asio, loading SFML")

# Loading SFML library
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.6.x"
)

FetchContent_GetProperties(sfml)
if (NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif ()
FetchContent_MakeAvailable(sfml)

message("Finished loading sfml")

# Loading nlohmann/json library
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
    SYSTEM
)
FetchContent_MakeAvailable(json)

message("Finished loading json")

# Warning flags
set(GCC_WARNING_FLAGS
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
    -Wlogical-op -Wno-null-dereference -Wuseless-cast -Wno-pragmas)

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
    -Wno-documentation
    -Wno-deprecated-copy-with-user-provided-dtor
    -Wno-return-type-c-linkage
    -Wno-suggest-destructor-override
    -Wno-signed-enum-bitfield
    -Wno-weak-vtables)

if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 13.0.0)
    set(CLANG_WARNING_FLAGS "${CLANG_WARNING_FLAGS} -Wno-return-std-move-in-c++11")
endif()

if (NOT WIN32)
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
        -Wno-switch-default
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wdouble-promotion
        -Wformat=2
        -Wno-effc++
        -Wno-suggest-override
        -Wno-null-dereference
        -Wno-zero-as-null-pointer-constant
        -Wno-padded
        -Wno-language-extension-token
    )
endif ()

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
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
  CACHE STRING
  "Choose the type of build, options are: None Debug Release tsan"
  FORCE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
elseif (CMAKE_BUILD_TYPE MATCHES "tsan")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=thread -O2 -g")
elseif (CMAKE_BUILD_TYPE MATCHES "Release" AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-exception-parameter -Wno-unused-variable")
endif ()

# Clang-tidy
if(USE_CLANG_TIDY)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
      if(DEFINED RTYPE_CLANG_TIDY_FLAGS)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE} ${RTYPE_CLANG_TIDY_FLAGS}")
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
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(WARNING_FLAGS ${WARNING_FLAGS})
else()
  error("${CMAKE_CXX_COMPILER_ID}: Unsupported compiler.")
endif()

message("Warning flags: ${Cyan} ${WARNING_FLAGS}${ColourReset}")

# for library compilation => shared libraries of game engine, utils, etc
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libs)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# need to first load this one to load library
add_subdirectory(RType-Utils)

add_subdirectory(GameEngine)
add_subdirectory(Server)
add_subdirectory(Client)

if (RTYPE_BUILD_TESTS)
    message("${BoldYellow}Building tests${ColourReset}")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/tests)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "v1.14.x"
        OVERRIDE_FIND_PACKAGE)
    if (WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(Server/tests)
    add_subdirectory(Client/tests)
    add_subdirectory(RType-Utils/tests/)
    add_subdirectory(GameEngine/tests/ECS/)
    add_subdirectory(GameEngine/tests/Physics/)
endif()

if (RTYPE_BUILD_BENCHMARKS)
    message("${BoldYellow}Building benchmarks${ColourReset}")
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "v1.14.x"
        OVERRIDE_FIND_PACKAGE)
    if (WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(benchmarks)
endif()

if (CMAKE_BUILD_TYPE MATCHES "Release")
    install(TARGETS r-type_client RUNTIME DESTINATION bin)
    install(TARGETS rtype-client-core RUNTIME DESTINATION bin)
    install(TARGETS r-type-ecs RUNTIME DESTINATION bin)
    install(TARGETS r-type-graphics RUNTIME DESTINATION bin)
    install(TARGETS r-type-physics RUNTIME DESTINATION bin)
    install(TARGETS r-type-utils RUNTIME DESTINATION bin)
    install(TARGETS r-type_server RUNTIME DESTINATION bin)
    install(TARGETS rtype-server-core RUNTIME DESTINATION bin)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION bin)
    set(CPACK_PACKAGE_NAME "R-Type-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_VERSION}")
    set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
    set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
    set(CPACK_SET_DESTDIR ${PROJECT_SOURCE_DIR})
    include(CPack)
endif ()
