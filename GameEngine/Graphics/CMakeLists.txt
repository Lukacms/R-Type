##
## CMakeLists: RType/Client
##

# interface libraries for .h files
add_library(r-type-graphics-interface INTERFACE)
set_property(TARGET r-type-graphics-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    r-type-graphics-interface INTERFACE
    r-type-utils
    sfml-window
    sfml-graphics
    sfml-system
)

add_library(
    r-type-graphics SHARED
    src/rtype/SFML/SFMLGraphicModule.cpp
    src/rtype/SFML/InputManager.cpp
    src/rtype/SFML/Systems/AnimationSystem.cpp
    src/rtype/EntryPoint.cpp
    src/rtype/SFML/Systems/SpriteComponent.cpp
    src/rtype/SFML/Systems/AnimationComponent.cpp
)

target_compile_features(r-type-graphics PRIVATE cxx_std_20)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
target_include_directories(r-type-graphics PRIVATE
    ./include
    ../ECS/include
    ../../RType-Utils/include
    ../../GameEngine/Graphics/include)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    r-type-graphics PRIVATE
    r-type-ecs-interface
    r-type-graphics-interface
    r-type-ecs
    r-type-utils
    nlohmann_json::nlohmann_json
    sfml-window
    sfml-graphics
    sfml-system
)
