##
## CMakeLists: R-Type / Client
##

# project name
project(r-type_client)

# include directories
include_directories(include/)

# if shared libraries need to have template files
add_library(rtype-client-interface INTERFACE)

# link the library
set_property(TARGET rtype-client-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-client-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-client-interface INTERFACE
    r-type-utils
    r-type-ecs
    r-type-audio
    r-type-graphics-interface
    r-type-graphics
    asio::asio
    nlohmann_json::nlohmann_json
)

# add library with all of the source file, execpt for the main

add_library(
    rtype-client-core
    SHARED
    src/rtype/Client.cpp
    src/rtype/config/ArgsConfig.cpp
    src/Factory/ClientEntityFactory.cpp
    src/rtype/scenes/Menu.cpp
    src/rtype/scenes/PauseMenu.cpp
    src/rtype/scenes/Lounge.cpp
    src/rtype/scenes/Game.cpp
    src/rtype/components/Room.cpp
        src/rtype/Background/BackgroundManager.cpp
)

target_compile_features(rtype-client-core PRIVATE cxx_std_20)
target_compile_options(rtype-client-core PRIVATE ${WARNING_FLAGS})
target_include_directories(
    rtype-client-core
    PUBLIC
    ../GameEngine/ECS/include/
    ../GameEngine/Graphics/include/
    ../GameEngine/Physics/include/
    ../GameEngine/Audio/include/
    ../RType-Utils/include/
)
set_property(TARGET rtype-client-core PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-client-core PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-client-core PRIVATE
    rtype-client-interface
    r-type-graphics-interface
    r-type-utils
    nlohmann_json::nlohmann_json
    asio::asio # link asio library to core
)

message("${BoldWhite}Finished loading rtype-client-core${ColourReset}")

# add the executable with the main
add_executable(
    r-type_client
    src/main.cpp
)

# link the libraries to executable
target_link_libraries(
    r-type_client PRIVATE
    rtype-client-core
    rtype-client-interface
)
if (NOT WIN32)
    target_link_options(r-type_client PRIVATE -rdynamic)
endif ()
target_compile_features(r-type_client PRIVATE cxx_std_20)
target_compile_options(r-type_client PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type_client PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED ON)
