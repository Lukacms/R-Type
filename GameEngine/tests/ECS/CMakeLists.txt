##
## CMakeLists: Server / tests
##

cmake_minimum_required(VERSION 3.6)

enable_testing()

add_executable(
    tests-r-type_ecs
        src/testSparseArray.cpp
        src/testECSManager.cpp
    )
target_compile_options(tests-r-type_ecs PRIVATE ${WARNING_FLAGS})
target_include_directories(tests-r-type_ecs PUBLIC ../../ECS/include/)
target_link_libraries(
    tests-r-type_ecs PRIVATE
    r-type-ecs-interface
    r-type-ecs
    GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests-r-type_ecs)
