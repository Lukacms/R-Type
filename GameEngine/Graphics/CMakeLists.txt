##
## CMakeLists: RType/Client
##

add_library(r-type-graphics SHARED
    src/rtype/GraphicModule.cpp
    src/rtype/InputManager.cpp
    src/rtype/EntryPoint.cpp
)


target_include_directories(r-type-graphics PRIVATE ./include ../ECS/include)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
target_link_libraries(r-type-graphics PRIVATE r-type-ecs-interface)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)
