cmake_minimum_required(VERSION 3.6)

project(r-type)

set(PROJECT_SOURCE_DIR .)

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

message("Finished loading Asio")

# for library compilation => shared libraries of game engine, utils, etc
set(LIBRARY_OUTPUT_PATH ${r-type_SOURCE_DIR}/libs)

# need to first load this one to load library
add_subdirectory(RType-Utils)

add_subdirectory(GameEngine)
add_subdirectory(Server)
add_subdirectory(Client)
