# disable cmake warnings for dependencies
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
# honor normal variables in options
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(OLD_CMAKE_FLAGS CMAKE_CXX_FLAGS)
set(CMAKE_CXX_FLAGS "-w -Wno-unsafe-buffer-usage -Wno-documentation")

if (RTYPE_BUILD_TESTS)
    set(OLD_CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD})
    set(CMAKE_CXX_STANDARD 17)
    set(CATCH_BUILD_STATIC_LIBRARY ON)
    add_subdirectory(GTests)
    set(CMAKE_CXX_STANDARD ${OLD_CMAKE_CXX_STANDARD})
    unset(OLD_CMAKE_CXX_STANDARD)
endif()
