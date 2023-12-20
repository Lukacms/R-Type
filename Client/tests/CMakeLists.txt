##
## CMakeLists: Client / tests
##

cmake_minimum_required(VERSION 3.6)

enable_testing()

add_executable(
    tests-r-type_client
    src/main.cpp
    )
target_compile_options(tests-r-type_client PRIVATE ${WARNING_FLAGS})
target_include_directories(tests-r-type_client PUBLIC ${PROJECT_SOURCE_DIR}/Client/include)
target_link_libraries(
    tests-r-type_client PRIVATE
    rtype-client-core
    rtype-client-interface
    GTest::gtest_main
    r-type-ecs
    r-type-graphics
)
include(GoogleTest)
gtest_discover_tests(tests-r-type_client)
