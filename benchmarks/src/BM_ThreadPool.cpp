/*
** EPITECH PROJECT, 2023
** src
** File description:
** BM_ThreadPool
*/

#include <benchmark/benchmark.h>
#include <cstdlib>
#include <iostream>
#include <rtype/clients/ThreadPool.hh>

constexpr int ITERATIONS{50000};

static void bm_thread_pool(benchmark::State &state)
{
    rserver::ThreadPool pool{};
    auto res{0};

    auto lamda{[&res]() mutable {
        int add{rand() % 100}; // NOLINT
        res += add;
    }};

    for (auto _ : state) { // NOLINT
        pool.add_job(lamda);
    }

    std::cout << res << "\n";
    pool.stop();
}

BENCHMARK(bm_thread_pool)->Iterations(ITERATIONS);
