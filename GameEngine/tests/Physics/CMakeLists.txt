##
## CMakeLists: Server / tests
##

cmake_minimum_required(VERSION 3.6)

enable_testing()

add_executable(
    tests-r-type_physics
    src/testPhysicsManager.cpp
    )
target_compile_options(tests-r-type_physics PRIVATE ${WARNING_FLAGS})
target_include_directories(tests-r-type_physics PUBLIC ../../Physics/include/ ../../ECS/include)
target_link_libraries(
    tests-r-type_physics PRIVATE
    r-type-ecs-interface
    r-type-ecs
    r-type-physics
    GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests-r-type_physics)
