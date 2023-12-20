/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <algorithm>
#include <csignal>
#include <iostream>
#include <mutex>
#include <rtype.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Manager.hh>
#include <rtype/SparseArray.hpp>
#include <rtype/network/Network.hpp>
#include <unistd.h>

/**
 * @brief used to handle sigint, is atomic to be modified between the threads
 */
static volatile std::atomic_int RUNNING = 1;

/**
 * @brief array of method pointers to handle commands recieved from client
 */
static const std::vector<rserver::CommandHandler> HANDLER{
    {.type = ntw::Input, .handler = &rserver::Manager::input_handler},
};

/* constructors and destructors */

/**
 * @brief Default constructor
 *
 * @param port port_type, default to 8080
 */
rserver::Manager::Manager(asio::ip::port_type port)
    : udp_socket{this->context, asio::ip::udp::endpoint{asio::ip::udp::v4(), port}},
      logic{this->udp_socket}
{
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>(ECS_SL_PATH.data());

    SparseArray<rtype::TransformComponent> transform{};
    SparseArray<rtype::BoxColliderComponent> boxes{};
    SparseArray<rtype::TagComponent> tags{};
    SparseArray<rtype::HealthComponent> healths{};

    this->ecs.get_class().register_component(transform);
    this->ecs.get_class().register_component(boxes);
    this->ecs.get_class().register_component(tags);
    this->ecs.get_class().register_component(healths);
    DEBUG(("Constructed manager with port: %d%s", port, ENDL));
    std::signal(SIGINT, Manager::handle_disconnection);
    this->start_receive();
}

/**
 * @brief Constructor by move
 *
 * @param to_move - Manager &&
 */
rserver::Manager::Manager(rserver::Manager &&to_move)
    : udp_socket{std::move(to_move.udp_socket)}, logic{std::move(to_move.logic)}
{
}

/**
 * @brief Destructor. Stop threads and quit
 */
rserver::Manager::~Manager()
{
    this->threads.stop();
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

        manager.run_game_logic();
        manager.run();
    } catch (std::exception &e) {
        std::cout << e.what() << ENDL;
    }
}

/**
 * @brief call the method `run` on asio::udp::context. It blocks until all works has finished
 */
void rserver::Manager::run()
{
    this->context.run();
}

/**
 * @brief method to run game logic
 *  the game logic has to be on another thread, as the asio context run is an infinite loop
 * TODO
 */
void rserver::Manager::run_game_logic()
{
    this->threads.add_job([this]() {
        while (RUNNING) {
            // std::cout << "oui: " << this->players.length() << "\n";
            // sleep(1);
        }
        this->context.stop();
    });
}

/* send data to clients */
/**
 * @brief Send a message to a specific client
 *
 * @param to_send - Communication - struct containing message to send
 * @param client - Player - containing udp endpoint to send message to
 * @param udp_socket - socket - udp::socket to send message from
 */
void rserver::Manager::send_message(ntw::Communication &to_send, const Player &client,
                                    asio::ip::udp::socket &udp_socket)
{
    udp_socket.async_send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint(),
                             [](auto && /* p_h1 */, auto && /* p_h2 */) {});
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
    for (const auto &client : players.get_all_players()) {
        udp_socket.async_send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint(),
                                 [](auto && /* p_h1 */, auto && /* p_h2 */) {});
    }
}

/* async udp methods */
void rserver::Manager::start_receive()
{
    ntw::Communication commn{};

    while (RUNNING) {
        this->udp_socket.receive_from(asio::buffer(&commn, sizeof(commn)), this->endpoint);
        /* this->udp_socket.async_receive_from(
            asio::buffer(&commn, sizeof(commn)), this->endpoint,
            [this](auto &&p_h1, auto &&p_h2) { handle_receive(p_h1, p_h2); }); */
        DEBUG(("port upon recieving %d\n", this->endpoint.port()));
        DEBUG(("arguments here: %s\n", commn.args.data()));
        if (this->endpoint.port() > 0)
            this->threads.add_job(
                [commn, this]() { this->command_manager(commn, this->endpoint); });
    }
}

void rserver::Manager::handle_receive(const asio::error_code &error,
                                      std::size_t /* bytes_transferre */)
{
    if (!error) {
        this->start_receive();
    }
}

void rserver::Manager::handle_send(const ntw::Communication & /*message*/,
                                   const asio::error_code & /*error*/,
                                   std::size_t /*bytes_transferred*/)
{
}

void rserver::Manager::command_manager(ntw::Communication communication,
                                       asio::ip::udp::endpoint client)
{
    std::vector<std::string> args{
        split_delimitor(communication.args.data(), ntw::DELIMITORS.data())};

    try {
        Player &player{this->players.get_by_id(client.port())};

        {
            std::unique_lock<std::mutex> lock{player.mutex};
            for (const auto &handle : HANDLER) {
                if (handle.type == communication.type) {
                    handle.handler(*this, player, args);
                    return;
                }
            }
        }
    } catch (PlayersManager::PlayersException & /* e */) {
        if (this->players.length() >= 4) {
            this->refuse_client(client);
        } else {
            this->add_new_player(client);
        }
    }
}

void rserver::Manager::refuse_client(asio::ip::udp::endpoint &client)
{
    ntw::Communication communication{.type = ntw::Refusal, .args = {}};

    this->udp_socket.async_send_to(asio::buffer(&communication, sizeof(communication)), client,
                                   [this, communication](auto &&p_h1, auto &&p_h2) {
                                       handle_send(communication, p_h1, p_h2);
                                   });
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
