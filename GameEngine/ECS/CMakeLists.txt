##
## CMakeLists: R-Type / Client
##

add_library(r-type-ecs-interface INTERFACE)
target_include_directories(r-type-ecs-interface INTERFACE include)
target_link_libraries(
        r-type-ecs-interface INTERFACE
        nlohmann_json::nlohmann_json
)

add_library(r-type-ecs SHARED
    src/rtype/Entity.cpp
    src/rtype/SystemManager.cpp
    src/rtype/Systems/TransformSystem.cpp
    src/rtype/EntityManager.cpp
    src/rtype/EntryPoint.cpp
    src/rtype/Components.cpp
)

target_include_directories(
    r-type-ecs PRIVATE
    include
    ../../RType-Utils/include
)
target_compile_options(r-type-ecs PRIVATE ${WARNING_FLAGS})
target_link_libraries(
    r-type-ecs PRIVATE
    r-type-ecs-interface
    r-type-utils
    nlohmann_json::nlohmann_json
)
set_property(TARGET r-type-ecs PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-ecs PROPERTY CXX_STANDARD_REQUIRED ON)
