/*
** EPITECH PROJECT, 2023
** src
** File description:
** BM_PlayersManager
*/

#include <benchmark/benchmark.h>
#include <iostream>
#include <rtype/clients/PlayersManager.hh>

constexpr int ITERATIONS{500000};

static void bm_players_manager(benchmark::State &state)
{
    static rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    for (auto _ : state) { // NOLINT
        manager.add_player(endpoint);
    }

    try {
        manager.get_by_id(978); // NOLINT
    } catch (rserver::PlayersManager::PlayersException & /* e */) {
    }
}

BENCHMARK(bm_players_manager)->Iterations(ITERATIONS);
