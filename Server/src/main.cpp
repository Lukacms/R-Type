/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include "rtype/Factory/ServerEntityFactory.hh"
#include <iostream>
#include <rtype.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Manager.hh>
#include <rtype/config/ArgsParser.hh>

static int display_help()
{
    for (auto const &str : rserver::HELP_MSG) {
        std::cout << str << ENDL;
    }
    return rserver::SUCESS;
}

int main(int argc, const char *argv[])
{
    // ServerEntityFactory factory{};
    // rtype::ECSManager ecsManager{};
    // SparseArray<rtype::HealthComponent> healthComponents{};
    // ecsManager.register_component<rtype::HealthComponent>(healthComponents);
    // size_t id {factory.create("Enemy", ecsManager)};
    // std::cout << ecsManager.get_component<rtype::HealthComponent>(id).health;
    try {
        rserver::Infos infos{
            rserver::ArgsParser::get_args(argc, std::span(argv, std::size_t(argc)))};

        if (infos.help)
            return display_help();
        rserver::Manager::launch(rserver::DEFAULT_PORT);
    } catch (rserver::ArgsParser::ArgsException &e) {
        std::cout << e.what() << ENDL;
        return rserver::FAILURE;
    }

    return rserver::SUCESS;
}
