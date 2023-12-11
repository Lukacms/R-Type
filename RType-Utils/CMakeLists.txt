# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# project name
project(r-type-utils)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# only add the interface library
add_library(r-type-utils INTERFACE)

# properties
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD_REQUIRED ON)
