##
## CMakeLists: R-Type / Client
##

# project name
project(r-type_client)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/..)

# include directories
include_directories(include/)

# if shared libraries need to have template files
add_library(rtype-client-interface INTERFACE)

# link the library
set_property(TARGET rtype-client-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-client-interface PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
        rtype-client-interface INTERFACE
        asio::asio
)

# add library with all of the source file, execpt for the main

add_library(
    rtype-client-core
    SHARED
    src/launch.cpp
    src/rtype/Client.cpp
    src/rtype/Network/NetworkManager.cpp
)

target_compile_features(rtype-client-core PRIVATE cxx_std_20)
target_compile_options(rtype-client-core PRIVATE ${WARNING_FLAGS})
target_include_directories(
    rtype-client-core
    PUBLIC
    include
    ../Network/include/
    ../GameEngine/ECS/include/
    ../GameEngine/Graphics/include/
    ../GameEngine/Physics/include
    ../RType-Utils/include/
    ../GameEngine/Graphics/include
    ${CMAKE_BINARY_DIR}/_deps/sfml-src/include)
set_property(TARGET rtype-client-core PROPERTY CXX_STANDARD 20)
set_property(TARGET rtype-client-core PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    rtype-client-core PRIVATE
    rtype-client-interface
    asio::asio # link asio library to core
    r-type-utils
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
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
    asio::asio # link asio library to core
    r-type-ecs
    r-type-graphics
    r-type-physics
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
    )
target_link_options(r-type_client PRIVATE -rdynamic)
target_compile_features(r-type_client PRIVATE cxx_std_20)
target_compile_options(r-type_client PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type_client PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED ON)
