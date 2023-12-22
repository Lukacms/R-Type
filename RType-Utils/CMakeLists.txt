# project name
project(r-type-utils)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

if (WIN32)
    include(FetchContent)
    FetchContent_Declare(
        dlfcn-win32
        GIT_REPOSITORY "https://github.com/dlfcn-win32/dlfcn-win32.git"
        GIT_TAG "v1.4.1"
        SYSTEM
    )
    FetchContent_MakeAvailable(dlfcn-win32)
endif()

# only add the interface library
add_library(r-type-utils INTERFACE)

# properties
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD_REQUIRED ON)
if (WIN32)
    find_package(dlfcn-win32 REQUIRED)
    target_include_directories(r-type-utils INTERFACE ${CMAKE_BINARY_DIR}/_deps/dlfcn-win32-src/src)
    target_link_libraries(r-type-utils INTERFACE dlfcn-win32::dl)
endif()
