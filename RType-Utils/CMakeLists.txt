# project name
project(r-type-utils)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

include_directories(include/)

if (WIN32)
    include(FetchContent)
    FetchContent_Declare(
        dlfcn-win32
        GIT_REPOSITORY "https://github.com/dlfcn-win32/dlfcn-win32.git"
        # GIT_TAG "v1.5.0" # when the merge request will be accepted
        GIT_TAG "fix49" # while waiting for pr
        SYSTEM
    )
    FetchContent_MakeAvailable(dlfcn-win32)
    set(CMAKE_DL_LIBS dlfcn-win32::dl)
endif ()

# only add the interface library
add_library(
    r-type-utils SHARED
    src/utils/Clock.cpp
)

# properties
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-utils PROPERTY CXX_STANDARD_REQUIRED ON)
if (WIN32)
    target_link_libraries(r-type-utils PRIVATE ${CMAKE_DL_LIBS})
    # target_include_directories(r-type-utils PRIVATE ${CMAKE_BINARY_DIR}/_deps/dlfcn-win32-src/src)
endif()
