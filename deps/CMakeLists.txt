# disable cmake warnings for dependencies
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
# honor normal variables in options
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(OLD_CMAKE_FLAGS CMAKE_CXX_FLAGS)
set(CMAKE_CXX_FLAGS "-w -Wno-unsafe-buffer-usage -Wno-documentation")

set(SFML_STATIC_LIBRARIES FALSE)
set(BUILD_SHARED_LIBS TRUE)
add_subdirectory(SFML SYSTEM)

set(CMAKE_CXX_FLAGS OLD_CMAKE_FLAGS)
unset(OLD_CMAKE_FLAGS)

if (RTYPE_BUILD_TESTS)
    set(OLD_CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD})
    set(CMAKE_CXX_STANDARD 17)
    set(CATCH_BUILD_STATIC_LIBRARY ON)
    add_subdirectory(GTests)
    set(CMAKE_CXX_STANDARD ${OLD_CMAKE_CXX_STANDARD})
    unset(OLD_CMAKE_CXX_STANDARD)
endif()

# glfw
add_subdirectory(glfw EXCLUDE_FROM_ALL)

# glew
add_definitions(-DGLEW_SHARED)
add_subdirectory(glew EXCLUDE_FROM_ALL)
add_library(glew ALIAS libglew_shared)
