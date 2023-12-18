##
## CMakeLists: RType/Client
##

add_library(r-type-graphics SHARED
    src/rtype/AudioManager.cpp
    src/rtype/InputManager.cpp
    src/rtype/SceneManager.cpp
    src/rtype/SpriteManager.cpp
    src/rtype/WindowManager.cpp
    src/rtype/TextureManager.cpp
    src/rtype/Systems/SpriteSystem.cpp
    src/rtype/Systems/MovementSystem.cpp
    src/rtype/Systems/AnimationSystem.cpp
    )


target_include_directories(r-type-graphics PRIVATE ./include ../ECS/include/)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
target_link_libraries(r-type-graphics PRIVATE r-type-ecs-interface)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)