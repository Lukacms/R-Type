/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Solo
*/

#include <algorithm>
#include <rtype/GameLogic/solo/Solo.hh>
#include <rtype/Manager.hh>
#include <rtype/utils.hpp>

/* ctor / dtor */
rserver::game::solo::SoloGame::SoloGame(asio::ip::udp::socket &psocket,
                                        asio::ip::udp::endpoint &pendpoint)
    : game{psocket, this->ecs_mutex}, player{pendpoint}, socket{psocket}
{
#ifdef __linux
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>(ECS_SL_PATH.data());
#else
    this->ecs.init_class<void *()>(ECS_SL_PATH.data());
#endif /* __linux */
    init_ecs(this->ecs.get_class());
}

rserver::game::solo::SoloGame::SoloGame(rserver::game::solo::SoloGame &&to_move)
    : game{std::move(to_move.game)}, player{std::move(to_move.player)}, ai{std::move(to_move.ai)},
      socket{to_move.socket}
{
}

rserver::game::solo::SoloGame &rserver::game::solo::SoloGame::operator=(SoloGame &&to_move)
{
    this->ai = std::move(to_move.ai);
    this->socket = std::move(to_move.socket);
    this->player = std::move(to_move.player);
    this->ecs = std::move(to_move.ecs);
    return *this;
}
