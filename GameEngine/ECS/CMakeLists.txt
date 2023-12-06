##
## CMakeLists: R-Type / Client
##

add_library(r-type-ecs SHARED
    src/rtype/Entity.cpp
    src/rtype/SystemManager.cpp
    src/launch.cpp
    src/rtype/Systems/SpriteSystem.cpp
    src/rtype/Systems/MovementSystem.cpp
    src/rtype/Systems/TransformSystem.cpp

    )

target_include_directories(r-type-ecs PRIVATE ./include)
target_compile_options(r-type-ecs PRIVATE ${WARNING_FLAGS})
#target_link_libraries(r-type-ecs PRIVATE raytracer-interface)
set_property(TARGET r-type-ecs PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-ecs PROPERTY CXX_STANDARD_REQUIRED ON)
