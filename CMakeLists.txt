project(r-type)

cmake_minimum_required(VERSION 3.6)

set(PROJECT_SOURCE_DIR .)

# fetch asio library which is used by both client and server
message("Loading Asio library")

option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
  ASIO_CPM_FETCHCONTENT_COMPAT
  "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
  ON
)
# Download this repository
include(FetchContent)
FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

message("Finished loading Asio")

add_subdirectory(Client)
add_subdirectory(GameEngine)
add_subdirectory(Server)
