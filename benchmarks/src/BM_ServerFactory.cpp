/*
** EPITECH PROJECT, 2023
** src
** File description:
** BM_ServerFactory
*/

#include <benchmark/benchmark.h>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/dlloader/DlLoader.hpp>

constexpr int ITERATIONS{1000};

static void bm_server_factory(benchmark::State &state)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    rtype::SparseArray<rtype::BoxColliderComponent> boxes{};
    rtype::SparseArray<rtype::TransformComponent> transform{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::HealthComponent> healths{};
    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");

    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    for (auto _ : state) { // NOLINT
        rserver::ServerEntityFactory::create("BasicEnemy", ecs.get_class());
        rserver::ServerEntityFactory::create("Player", ecs.get_class());
        rserver::ServerEntityFactory::create("OtherPlayer", ecs.get_class());
        rserver::ServerEntityFactory::create("Bullet", ecs.get_class());
    }
}

BENCHMARK(bm_server_factory)->Iterations(ITERATIONS);
