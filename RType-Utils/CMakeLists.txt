# project name
project(r-type-utils)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

include_directories(include/)

# only add the interface library
add_library(
    r-type-utils SHARED
    src/utils/Clock.cpp
    src/utils/Vector2D.cpp
    src/utils/Colors.cpp
    src/utils/ThreadPool.cpp
)
target_link_libraries(
    r-type-utils PRIVATE
    nlohmann_json::nlohmann_json
)

# properties
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD_REQUIRED ON)
