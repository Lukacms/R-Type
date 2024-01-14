##
## CMakeLists: R-Type / Client
##

add_library(r-type-audio SHARED
    src/rtype/SFML/BGMManager.cpp
    src/rtype/SFML/SFXManager.cpp
    src/rtype/SFML/SFMLAudioModule.cpp
    src/rtype/AudioModuleException.cpp
    src/rtype/EntryPoint.cpp
)

target_include_directories(r-type-audio PRIVATE
    include/
    ../../RType-Utils/include
)
target_compile_options(r-type-audio PRIVATE ${WARNING_FLAGS})
target_link_libraries(r-type-audio PRIVATE
    r-type-ecs-interface
    r-type-ecs
    r-type-utils
    nlohmann_json::nlohmann_json
    sfml-system
    sfml-audio
)
set_property(TARGET r-type-audio PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-audio PROPERTY CXX_STANDARD_REQUIRED ON)
