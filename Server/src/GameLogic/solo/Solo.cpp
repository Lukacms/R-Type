/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Solo
*/

#include <algorithm>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/GameLogic/solo/Solo.hh>
#include <rtype/Manager.hh>
#include <rtype/utils.hpp>
#include <shared_mutex>

/* ctor / dtor */
rserver::game::solo::SoloGame::SoloGame(asio::ip::udp::socket &psocket, Player &pplayer)
    : game{psocket, this->ecs_mutex, 0}, player{pplayer}, socket{psocket}
{
#ifdef __linux
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>(ECS_SL_PATH.data());
    this->physics.init_class<std::unique_ptr<rtype::PhysicsManager>()>(PHYSICS_SL_PATH.data());
#else
    this->ecs.init_class<void *()>(ECS_SL_PATH.data());
    this->physics.init_class<void *()>(PHYSICS_SL_PATH.data());
#endif /* __linux */
    init_ecs(this->ecs.get_class());
    this->player.set_entity_value(ServerEntityFactory::create("Player", this->ecs.get_class()));
}

rserver::game::solo::SoloGame::SoloGame(rserver::game::solo::SoloGame &&to_move)
    : game{std::move(to_move.game)}, player{to_move.player}, ai{std::move(to_move.ai)},
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

void rserver::game::solo::SoloGame::game_turn(rtype::utils::Clock &clock)
{
    std::unique_lock<std::shared_mutex> lock{this->mutex};

    try {
        this->game.game_loop(this->physics.get_class(), this->player, this->ecs.get_class(),
                             static_cast<float>(clock.get_elapsed_time_in_ms()));
    } catch (SoloGame::SoloException &e) {
        throw e;
    }
    this->ecs.get_class().apply_system(static_cast<float>(clock.get_elapsed_time_in_ms()));
}

rserver::Player &rserver::game::solo::SoloGame::get_player() const
{
    return this->player;
}

void rserver::game::solo::SoloGame::add_move_to_friend(const int &move)
{
    for (auto &bro : this->ai) {
        bro.add_move_to_queue(move);
    }
}

void rserver::game::solo::SoloGame::delete_friend(const std::size_t &entity_id)
{
    for (auto bro{this->ai.begin()}; bro != this->ai.end(); bro++) {
        if (bro->get_entity_id() == entity_id) {
            this->ai.erase(bro);
            break;
        }
    }
}

void rserver::game::solo::SoloGame::end_game()
{
    this->player.set_status(rserver::PlayerStatus::Lobby);
    throw SoloException(END.data());
}

rtype::ECSManager &rserver::game::solo::SoloGame::get_ecs() const
{
    return this->ecs.get_class();
}

std::shared_mutex &rserver::game::solo::SoloGame::get_mutex()
{
    return this->ecs_mutex;
}

/* exception */
rserver::game::solo::SoloGame::SoloException::SoloException(const std::string &perror)
    : error{std::move(perror)}
{
}

const char *rserver::game::solo::SoloGame::SoloException::what() const noexcept
{
    return this->error.c_str();
}
