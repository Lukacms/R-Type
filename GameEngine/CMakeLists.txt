##
## CMakeLists: R-Type / Client
##

include_directories(${CMAKE_BINARY_DIR}/_deps/sfml-src/include)

add_subdirectory(ECS)
add_subdirectory(Graphics)
add_subdirectory(Physics)
