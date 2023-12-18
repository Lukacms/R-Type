cmake_minimum_required(VERSION 3.6)

project(r-type)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(PROJECT_SOURCE_DIR .)

#add_subdirectory(deps)

# option to build tests
option(RTYPE_BUILD_TESTS "Build the tests" OFF)

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

message("Finished loading Asio")

FetchContent_MakeAvailable(asiocmake)

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
    set(CLANG_WARNING_FLAGS "${CLANG_WARNING_FLAGS} -Wno-return-std-move-in-c++11")
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
    -Wno-switch-default
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wdouble-promotion
    -Wformat=2
    -Weffc++
    -Wno-suggest-override
    -Wno-suggest-destructor-override
    -Wno-documentation
    -Wno-zero-as-null-pointer-constant
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
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
  CACHE STRING
  "Choose the type of build, options are: None Debug Release tsan"
  FORCE)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
elseif(CMAKE_BUILD_TYPE MATCHES "tsan")
  set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=thread")
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

# for library compilation => shared libraries of game engine, utils, etc
set(LIBRARY_OUTPUT_PATH ${r-type_SOURCE_DIR}/libs)

# need to first load this one to load library
add_subdirectory(RType-Utils)

add_subdirectory(GameEngine)
add_subdirectory(Server)
add_subdirectory(Client)
