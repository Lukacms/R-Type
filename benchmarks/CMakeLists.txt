cmake_minimum_required(VERSION 3.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/benchmarks)

include(FetchContent)

option(BENCHMARK_DOWNLOAD_DEPENDENCIES "download its dependencies" ON)
# option(GOOGLETEST_PATH "path to googletests" ${CMAKE_BINARY_DIR}/_deps/)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY "https://github.com/google/benchmark.git"
    GIT_TAG "main"
    SYSTEM
)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(
    rtype_benchmarks
    src/main.cpp
    src/BM_ServerFactory.cpp
    # src/BM_ClientFactory.cpp
    src/BM_ThreadPool.cpp
    src/BM_PlayersManager.cpp
)

target_compile_options(rtype_benchmarks PRIVATE ${WARNING_FLAGS})
target_include_directories(
    rtype_benchmarks PUBLIC
    ${PROJECT_SOURCE_DIR}/Server/include
    ${PROJECT_SOURCE_DIR}/Client/include
)
target_link_libraries(
    rtype_benchmarks PRIVATE
    rtype-server-core
    rtype-server-interface
    rtype-client-core
    rtype-client-interface
    benchmark::benchmark
)
