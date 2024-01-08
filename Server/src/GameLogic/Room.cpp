/*
** EPITECH PROJECT, 2023
** GameLogic
** File description:
** Room
*/

#include <rtype.hh>
#include <rtype/GameLogic/Room.hh>
#include <rtype/Manager.hh>

/* constructors / destructors */
rserver::game::Room::Room(asio::ip::udp::socket &psocket, PlayersManager &pmanager, std::size_t pid)
    : socket{psocket}, id{std::move(pid)}, logic{socket, ecs_mutex}, manager{pmanager}
{
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>(ECS_SL_PATH.data());
    this->physics.init_class<std::unique_ptr<rtype::PhysicsManager>()>(PHYSICS_SL_PATH.data());
    init_ecs(this->ecs.get_class());
    DEBUG(("New game room created%s", ENDL));
}

rserver::game::Room::Room(rserver::game::Room &&to_move)
    : socket{to_move.socket}, id{std::move(to_move.id)}, logic{std::move(to_move.logic)},
      manager{to_move.manager}, status{std::move(to_move.status)}
{
}

rserver::game::Room::~Room()
{
    DEBUG(("Game room %zu deleted%s", this->id, ENDL));
}

/* methods */
void rserver::game::Room::add_player(Player &new_player)
{
    if (this->status != RoomStatus::Waiting)
        throw RoomException("Can't add player. Room is in a game.");
    if (this->players.size() >= MAX_PLAYERS)
        throw RoomException("Already max number of players");
    this->players.emplace_back(new_player.get_port());
    if (this->players.size() == 2) {
        this->status = RoomStatus::Waiting;
        this->timeout_connect.reset();
    } else if (this->players.size() == MAX_PLAYERS)
        this->status = RoomStatus::InGame;
    // Manager::send_message({}, new_player.get(), this->socket);
}

const rserver::game::RoomStatus &rserver::game::Room::get_status() const
{
    return this->status;
}

std::size_t rserver::game::Room::get_nb_players() const
{
    return this->players.size();
}

void rserver::game::Room::del_player(rserver::Player &to_del)
{
    for (auto player{this->players.begin()}; player != this->players.end(); player++) {
        if (to_del.get_port() == *player) {
            to_del.set_status(PlayerStatus::Lobby);
            this->players.erase(player);
            if (this->players.size() < 2)
                this->status = RoomStatus::Lounge;
            return;
        }
    }
    throw RoomException("There are no matching player in this room.");
}

std::size_t rserver::game::Room::get_id() const
{
    return this->id;
}

rserver::game::GameLogic &rserver::game::Room::get_logic()
{
    return this->logic;
}

void rserver::game::Room::run_game_logic(rtype::utils::Clock &delta)
{
    this->logic.game_loop(this->physics.get_class(), this->manager, this->ecs.get_class(),
                          static_cast<float>(delta.get_elapsed_time_in_s()));
}

void rserver::game::Room::check_wait_timeout()
{
    if (this->status != RoomStatus::Waiting)
        return;
    if (this->timeout_connect.get_elapsed_time_in_s() > TIMEOUT_WAITING) {
        this->status = RoomStatus::InGame;
        for (auto pid : this->players) {
            Manager::send_message({ntw::NetworkType::ToGame}, this->manager.get_by_id(pid),
                                  this->socket);
        }
    }
}

bool rserver::game::Room::has_player(const Player &player)
{
    for (auto &port : this->players) { // NOLINT
        if (port == player.get_port())
            return true;
    }
    return false;
}

/* exception */
rserver::game::Room::RoomException::RoomException(std::string &&perror)
    : error_msg{std::move(perror)}
{
}

const char *rserver::game::Room::RoomException::what() const noexcept
{
    return this->error_msg.c_str();
}
