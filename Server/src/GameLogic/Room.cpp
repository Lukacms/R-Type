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
rserver::game::Room::Room(std::shared_mutex &pecs, asio::ip::udp::socket &psocket,
                          PlayersManager &pmanager, std::size_t pid)
    : socket{psocket}, ecs_mutex{pecs}, id{std::move(pid)}, logic{socket, ecs_mutex},
      manager{pmanager}
{
    DEBUG(("New game room created%s", ENDL));
}

rserver::game::Room::Room(rserver::game::Room &&to_move)
    : socket{to_move.socket}, ecs_mutex{to_move.ecs_mutex}, id{std::move(to_move.id)},
      logic{std::move(to_move.logic)}, manager{to_move.manager}, status{std::move(to_move.status)}
{
}

rserver::game::Room::~Room()
{
    DEBUG(("Game room %zu deleted%s", this->id, ENDL));
}

/* methods */
void rserver::game::Room::add_player(Player &new_player)
{
    if (this->status != Waiting)
        throw RoomException("Can't add player. Room is in a game.");
    if (this->players.size() >= MAX_PLAYERS)
        throw RoomException("Already max number of p>layers");
    this->players.emplace_back(new_player.get_port());
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
            this->players.erase(player);
            return;
        }
    }
    throw RoomException("There are no matching player in this room.");
}

std::size_t rserver::game::Room::get_id() const
{
    return this->id;
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
