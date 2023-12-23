##
## CMakeLists: R-Type / Client
##

add_library(r-type-physics SHARED
    src/rtype/PhysicsManager.cpp
    src/rtype/EntryPoint.cpp
)

target_include_directories(r-type-physics PRIVATE ./include ../ECS/include)
target_compile_options(r-type-physics PRIVATE ${WARNING_FLAGS})
target_link_libraries(r-type-physics PRIVATE r-type-ecs-interface)
set_property(TARGET r-type-physics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-physics PROPERTY CXX_STANDARD_REQUIRED ON)
