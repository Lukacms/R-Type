##
## CMakeLists: Server / tests
##

cmake_minimum_required(VERSION 3.6)

enable_testing()

add_executable(
    tests-r-type_server
    src/testsUtils.cpp
    src/config/testsArgsParser.cpp
    )
target_compile_options(tests-r-type_server PRIVATE ${WARNING_FLAGS})
target_include_directories(tests-r-type_server PUBLIC ${PROJECT_SOURCE_DIR}/Server/include)
target_link_libraries(
    tests-r-type_server PRIVATE
    rtype-server-core
    rtype-server-interface
    GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests-r-type_server)
