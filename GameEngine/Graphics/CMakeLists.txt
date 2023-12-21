##
## CMakeLists: RType/Client
##

add_library(
    r-type-graphics SHARED
    src/rtype/GraphicModule.cpp
    src/rtype/InputManager.cpp
    src/rtype/EntryPoint.cpp
)

target_compile_features(r-type-graphics PRIVATE cxx_std_20)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
target_include_directories(r-type-graphics PRIVATE ./include ../ECS/include ${CMAKE_BINARY_DIR}/_deps/sfml-src/include)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    r-type-graphics PRIVATE
    r-type-ecs-interface
    r-type-graphics-interface
    r-type-ecs
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
)

# interface libraries for .h files
add_library(r-type-graphics-interface INTERFACE)
set_property(TARGET r-type-graphics-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    r-type-graphics-interface INTERFACE
    r-type-graphics
    r-type-ecs
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
)
