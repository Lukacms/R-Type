##
## CMakeLists: R-Type / Server
##

# project name
project(r-type_server)

# include directories
include_directories(include/)

# if shared libraries need to have template files
add_library(rtype-server-interface INTERFACE)

# link the library
set_property(TARGET rtype-server-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-server-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_include_directories(rtype-server-interface INTERFACE
        include
        ../RType-Utils/include/
        ../GameEngine/ECS/include
        ../GameEngine/Physics/include
        ${CMAKE_BINARY_DIR}/_deps/json-src/include/)
target_link_libraries(
    rtype-server-interface INTERFACE
    r-type-ecs
    r-type-physics
    asio::asio
    )

# add library with all of the source file, execpt for the main
add_library(
    rtype-server-core SHARED
    src/Manager.cpp
    src/utils.cpp
    src/config/ArgsParser.cpp
    src/clients/Player.cpp
    src/clients/PlayersManager.cpp
    src/clients/ThreadPool.cpp
    src/GameLogic/GameLogic.cpp
    src/GameLogic/Room.cpp
    src/GameLogic/RoomsManager.cpp
    src/GameLogic/LevelManager/LevelManager.cpp
    src/Factory/ServerEntityFactory.cpp
    src/commands/input_handler.cpp
    src/commands/add_new_player.cpp
    src/commands/end_handler.cpp
    src/commands/lobby_handler.cpp
    src/commands/room_handler.cpp
    src/GameLogic/EnemySystems/KamikazeSystem.cpp
)

target_compile_features(rtype-server-core PRIVATE cxx_std_20)
target_compile_options(rtype-server-core PRIVATE ${WARNING_FLAGS})
set_property(TARGET rtype-server-core PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-server-core PRIVATE
    rtype-server-interface
    r-type-utils
    nlohmann_json::nlohmann_json
    asio::asio # link asio library to core
    )

message("${BoldWhite}Finished loading rtype-server-core${ColourReset}")

# add the executable with the main
add_executable(
    r-type_server
    src/main.cpp
)

# link the libraries to executable
target_link_libraries(
    r-type_server PRIVATE
    rtype-server-core
    rtype-server-interface
    )
target_link_options(r-type_server PRIVATE -rdynamic)
target_compile_features(r-type_server PRIVATE cxx_std_20)
target_compile_options(r-type_server PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type_server PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED ON)
