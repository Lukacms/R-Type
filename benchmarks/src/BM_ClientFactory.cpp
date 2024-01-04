/*
** EPITECH PROJECT, 2023
** src
** File description:
** BM_ServerFactory
*/

#include <rtype/Components/SpriteComponent.hh>
#include <benchmark/benchmark.h>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ClientEntityFactory.hh>
#include <rtype/dlloader/DlLoader.hpp>

constexpr int ITERATIONS{1000};

static void bm_server_factory(benchmark::State &state)
{
    dl::DlLoader<rtype::ECSManager> ecs{};
    SparseArray<rtype::BoxColliderComponent> boxes{};
    SparseArray<rtype::TransformComponent> transform{};
    SparseArray<rtype::TagComponent> tags{};
    SparseArray<rtype::SpriteComponent> sprites{};
    SparseArray<rtype::HealthComponent> healths{};
    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");

    ecs.get_class().register_component(transform);
    ecs.get_class().register_component(boxes);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(healths);
    ecs.get_class().register_component(sprites);
    for (auto _ : state) { // NOLINT
        try {
            rclient::ClientEntityFactory::create(1, "BasicEnemy", ecs.get_class());
            rclient::ClientEntityFactory::create(1, "Player", ecs.get_class());
            rclient::ClientEntityFactory::create(1, "OtherPlayer", ecs.get_class());
            rclient::ClientEntityFactory::create(1, "Bullet", ecs.get_class());
        } catch (std::out_of_range & /* e */) {
        }
    }
}

BENCHMARK(bm_server_factory)->Iterations(ITERATIONS);
