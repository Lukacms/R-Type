/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <algorithm>
#include <csignal>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <rtype.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Manager.hh>
#include <rtype/SparseArray.hpp>
#include <rtype/network/Network.hpp>
#include <rtype/utils/Clock.hh>

/**
 * @brief used to handle sigint, is atomic to be modified between the threads
 * The only downside of this variable is that it can't be put in a header file, it will not work
 */
static volatile std::atomic_int RUNNING{1};

/**
 * @brief array of method pointers to handle commands recieved from client
 */
static const std::vector<rserver::CommandHandler> HANDLER{
    {ntw::NetworkType::Input, &rserver::Manager::input_handler},
    {ntw::NetworkType::End, &rserver::Manager::end_handler},
    {ntw::NetworkType::Room, &rserver::Manager::room_handler},
    {ntw::NetworkType::Solo, &rserver::Manager::solo_handler},
};

/* constructors and destructors */

/**
 * @brief Default constructor
 *
 * @param port port_type, default to 8080
 */
rserver::Manager::Manager(asio::ip::port_type port)
    : udp_socket{this->context, asio::ip::udp::endpoint{asio::ip::udp::v4(), port}}
{
#ifdef __linux
    this->physics.init_class<std::unique_ptr<rtype::PhysicsManager>()>(PHYSICS_SL_PATH.data());
#else
    this->physics.init_class<void *()>(PHYSICS_SL_PATH.data());
#endif /* __linux */

    try {
        this->udp_socket.non_blocking(true);
        std::signal(SIGINT, Manager::handle_disconnection);
    } catch (std::exception & /* e */) {
        DEBUG(("This instance will stay blocking, clean <CTRL-C> will not work.\n"));
    }
    DEBUG(("Constructed manager with port: %d%s", port, ENDL));
}

/**
 * @brief Constructor by move
 *
 * @param to_move - Manager &&
 */
rserver::Manager::Manager(rserver::Manager &&to_move)
    : udp_socket{std::move(to_move.udp_socket)}, threads{std::move(to_move.threads)},
      rooms{std::move(to_move.rooms)}, physics{std::move(to_move.physics)}
{
}

/**
 * @brief Destructor. Stop threads and quit
 */
rserver::Manager::~Manager()
{
    ntw::Communication commn{ntw::NetworkType::End};

    {
        std::shared_lock<std::shared_mutex> lock{this->rooms_mutex};
        Manager::send_to_all(commn, this->players, this->udp_socket);
    }
    DEBUG(("Finished server%s", ENDL));
}

/* operator overload */

/**
 * @brief operator = to move
 *
 * @param to_move - Manager &&
 * @return Manager &
 */
rserver::Manager &rserver::Manager::operator=(Manager &&to_move)
{
    this->udp_socket = std::move(to_move.udp_socket);
    this->endpoint = std::move(to_move.endpoint);
    this->players = std::move(to_move.players);
    this->threads = std::move(to_move.threads);
    this->physics = std::move(to_move.physics);

    return *this;
}

/* methods */
/**
 * @brief static method to launch project.
 * Define Manager, run game logic on thread and start running asio networking
 *
 * @param port - port_type
 */
void rserver::Manager::launch(asio::ip::port_type port)
{
    try {
        Manager manager{port};

        manager.start_receive();
    } catch (std::exception &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    }
}

void load_entity_properties()
{
    std::string path = rserver::ENTITIES_FILE.data();
    std::ifstream file{path};

    if (!file) {
        return;
    }
    nlohmann::json json;
    file >> json;
    std::cout << json["Enemies"] << std::endl;
}

/**
 * @brief method to run game logic
 *  the game logic has to be on another thread, as the asio context run is an infinite loop
 */
void rserver::Manager::run_game_logic(rtype::utils::Clock &timer, rtype::utils::Clock &delta,
                                      std::mutex &clocks_mutex)
{
    this->threads.add_job([&, this]() {
        std::unique_lock<std::mutex> lock{clocks_mutex};

        load_entity_properties();
        if (timer.get_elapsed_time_in_ms() > game::TIMER) {
            this->run_all_rooms_logics(delta);
            this->run_solo_games(delta);
            timer.reset();
            delta.reset();
        }
    });
}

/**
 * @brief Assuming that it was called in @run_game_logic, when the clock is set, it launches the
 * game logic of all the rooms that running their game (not in waiting mode)
 *
 * @param delta - Clock -> the game logic seems to need delta time
 */
void rserver::Manager::run_all_rooms_logics(rtype::utils::Clock &delta)
{
    std::shared_lock<std::shared_mutex> lock{this->rooms_mutex};
    for (auto &room : this->rooms.get_rooms()) {
        if (room.get_status() == game::RoomStatus::InGame)
            room.run_game_logic(delta);
        else
            room.check_wait_timeout(static_cast<float>(delta.get_elapsed_time_in_ms()));
    }
}

void rserver::Manager::run_solo_games(rtype::utils::Clock &delta)
{
    std::shared_lock<std::shared_mutex> lock{this->solos_mutex};

    for (auto &solo : this->solos) {
        solo.game_turn(delta);
    }
}

/* send data to clients */
/**
 * @brief Send a message to a specific client
 *
 * @param to_send - Communication - struct containing message to send
 * @param client - Player - containing udp endpoint to send message to
 * @param udp_socket - socket - udp::socket to send message from
 */
void rserver::Manager::send_message(const ntw::Communication &to_send, Player &client,
                                    asio::ip::udp::socket &udp_socket)
{
    std::shared_lock<std::shared_mutex> lock{client.mutex};
    udp_socket.send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint());
}

/**
 * @brief Send message to all clients that the Manager has
 *
 * @param to_send
 * @param players
 * @param udp_socket
 */
void rserver::Manager::send_to_all(ntw::Communication &to_send, PlayersManager &players,
                                   asio::ip::udp::socket &udp_socket)
{
    for (auto &client : players.get_all_players()) {
        {
            std::shared_lock<std::shared_mutex> lock{client.mutex};
            udp_socket.send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint());
        }
    }
}

void rserver::Manager::send_message(const ntw::Communication &to_send,
                                    const PlayersManager &players,
                                    asio::ip::udp::socket &udp_socket, const PlayerStatus &status)
{
    for (auto &client : players.get_all_players()) {
        {
            std::shared_lock<std::shared_mutex> lock{client.mutex};
            if (client.get_status() == status) {
                udp_socket.send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint());
            }
        }
    }
}

void rserver::Manager::send_message(const ntw::Communication &to_send,
                                    const PlayersManager &players,
                                    asio::ip::udp::socket &udp_socket, const std::size_t &room_id)
{
    for (auto &client : players.get_all_players()) {
        {
            std::shared_lock<std::shared_mutex> lock{client.mutex};
            if (client.get_room_id() == static_cast<long>(room_id)) {
                udp_socket.send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint());
            }
        }
    }
}

/* async udp methods */
/**
 * @brief Handle network, messages recieved from clients. Also launched lobby functions that needs
 * to communicate with clients
 */
void rserver::Manager::start_receive()
{
    ntw::Communication commn{};
    rtype::utils::Clock clock{};
    rtype::utils::Clock timer{};
    rtype::utils::Clock delta{};
    std::mutex clocks_mutex{};

    while (RUNNING) {
        try {
            this->udp_socket.receive_from(asio::buffer(&commn, sizeof(commn)), this->endpoint);
            DEBUG(("port upon receiving %d\n", this->endpoint.port()));
            if (this->endpoint.port() > 0)
                this->threads.add_job(
                    [commn, this]() { this->command_manager(commn, this->endpoint); });
        } catch (std::exception & /* e */) {
            // DEBUG(("An exception has occured while recieving: %s\n", e.what()));
        }
        this->run_game_logic(timer, delta, clocks_mutex);
        if (clock.get_elapsed_time_in_ms() > game::TIMER) {
            this->lobby_handler();
            clock.reset();
        }
    }
}

/**
 * @brief Handle commands recieved from client. Redirect to another function depending on the type
 * of the communication struct
 *
 * @param communication - ntw::Communication - structure used to communicate
 * @param client - asio::endpoint - endpoint recieved from client. Allow to find which client sent
 * the message, or if new
 */
void rserver::Manager::command_manager(ntw::Communication const &communication,
                                       asio::ip::udp::endpoint &client)
{
    std::vector<std::string> args{
        split_delimitor(communication.args.data(), ntw::DELIMITORS.data())};

    try {
        Player &player{this->players.get_by_id(client.port())};
        std::shared_lock<std::shared_mutex> lock{player.mutex};

        for (const auto &handle : HANDLER) {
            if (handle.type == communication.type)
                return handle.handler(*this, player, args);
        }
    } catch (PlayersManager::PlayersException & /* e */) {
        this->add_new_player(client);
    } catch (ManagerException &e) {
        DEBUG(("Exception while handling commands: %s\n", e.what()));
    }
}

/**
 * @brief Refuse client to connect to server
 * @depreciated Was useful in previous version, in which there wasn't rooms
 *
 * @param client - asio::endpoint
 */
void rserver::Manager::refuse_client(asio::ip::udp::endpoint &client)
{
    ntw::Communication communication{ntw::NetworkType::Refusal};

    this->udp_socket.send_to(asio::buffer(&communication, sizeof(communication)), client);
}

/**
 * @brief get a Solo game by its player. Will throw if there isn't any solo game with this id
 *
 * @param player - Player &
 * @throws ManagerException
 */
rserver::game::solo::SoloGame &rserver::Manager::get_solo_game(rserver::Player &player)
{
    for (auto &solo : this->solos) {
        if (solo.get_player().get_port() == player.get_port())
            return solo;
    }
    throw ManagerException("There is no solo game for this player");
}

/**
 * @brief catch <CTRL-C> and stop server from running
 */
void rserver::Manager::handle_disconnection(int /*unused*/)
{
    RUNNING = 0;
}

/* exception */
rserver::Manager::ManagerException::ManagerException(std::string p_error)
    : error{std::move(p_error)}
{
}

const char *rserver::Manager::ManagerException::what() const noexcept
{
    return this->error.data();
}
