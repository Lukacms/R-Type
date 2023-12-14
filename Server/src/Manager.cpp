/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <csignal>
#include <iostream>
#include <rtype.hh>
#include <rtype/Manager.hh>
#include <rtype/network/Network.hpp>
#include <unistd.h>

static volatile std::atomic_int RUNNING = 1;

static const std::vector<rserver::CommandHandler> HANDLER{};

/* constructors and destructors */

/**
 * @brief Default constructor
 *
 * @param port port_type, default to 8080
 */
rserver::Manager::Manager(asio::ip::port_type port)
    : udp_socket{this->context, asio::ip::udp::endpoint{asio::ip::udp::v4(), port}}
{
    DEBUG(("Constructed manager with port: %d%s", port, ENDL));
    // std::signal(SIGINT, Manager::handle_disconnection);
}

rserver::Manager::Manager(rserver::Manager &&to_move) : udp_socket{std::move(to_move.udp_socket)}
{
}

rserver::Manager::~Manager()
{
    this->threads.stop();
    DEBUG(("Finished server%s", ENDL));
}

/* operator overload */

rserver::Manager &rserver::Manager::operator=(Manager &&to_move)
{
    this->udp_socket = std::move(to_move.udp_socket);

    return *this;
}

/* methods */
void rserver::Manager::launch(asio::ip::port_type port)
{
    try {
        Manager manager{port};

        manager.run_game_logic();
        manager.start_receive();
        manager.run();
    } catch (std::exception &e) {
        std::cout << e.what() << ENDL;
    }
}

void rserver::Manager::run()
{
    if (RUNNING)
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
            std::cout << "oui: " << this->players.length() << "\n";
            sleep(1);
        }
    });
}

/* send data to clients */
void rserver::Manager::send_message(ntw::Communication &to_send, const Player &client,
                                    asio::ip::udp::socket &udp_socket)
{
    udp_socket.async_send_to(asio::buffer(&to_send, sizeof(to_send)), client.get_endpoint(),
                             [](auto && /* p_h1 */, auto && /* p_h2 */) {});
}

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

    if (RUNNING) {
        this->udp_socket.async_receive_from(asio::buffer(&commn, sizeof(commn)), this->endpoint,
                                            [this](auto &&p_h1, auto &&p_h2) {
                                                handle_receive(std::forward<decltype(p_h1)>(p_h1),
                                                               std::forward<decltype(p_h2)>(p_h2));
                                            });
        if (this->endpoint.port() > 0)
            this->threads.add_job([&, this]() { this->command_manager(commn, endpoint); });
    } else {
        this->context.stop();
    }
}

void rserver::Manager::handle_receive(const asio::error_code &error,
                                      std::size_t /* bytes_transferre */)
{
    if (!error && RUNNING) {
        this->start_receive();
    } else {
        this->context.stop();
    }
}

void rserver::Manager::handle_send(const ntw::Communication & /*message*/,
                                   const asio::error_code & /*error*/,
                                   std::size_t /*bytes_transferred*/)
{
}

void rserver::Manager::command_manager(ntw::Communication &communication,
                                       asio::ip::udp::endpoint &client)
{
    std::vector<std::string> args{
        split_delimitor(std::string{communication.args.data()}, ntw::DELIMITORS.data())};

    try {
        Player &player{this->players.get_by_id(client.port())};

        for (const auto &handle : HANDLER) {
            if (handle.type == communication.type) {
                handle.handler(*this, player, args);
                return;
            }
        }
    } catch (PlayersManager::PlayersException & /* e */) {
        if (this->players.length() >= 4) {
            this->refuse_client(client);
        } else {
            this->players.add_player(client, this->udp_socket);
        }
    }
}

void rserver::Manager::refuse_client(asio::ip::udp::endpoint &client)
{
    ntw::Communication communication{.type = ntw::Refusal};

    this->udp_socket.async_send_to(asio::buffer(&communication, sizeof(communication)), client,
                                   [this, communication](auto &&p_h1, auto &&p_h2) {
                                       handle_send(communication,
                                                   std::forward<decltype(p_h1)>(p_h1),
                                                   std::forward<decltype(p_h2)>(p_h2));
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
