##
## CMakeLists: Server / tests
##

cmake_minimum_required(VERSION 3.6)

enable_testing()

add_executable(
    tests-r-type-utils
    src/testsNetwork.cpp
    src/testsDlLoader.cpp
    )
target_compile_options(tests-r-type-utils PRIVATE ${WARNING_FLAGS})
target_include_directories(tests-r-type-utils PUBLIC ${PROJECT_SOURCE_DIR}/RType-Utils/include)
target_link_libraries(
    tests-r-type-utils PRIVATE
    r-type-utils
    GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests-r-type-utils)
