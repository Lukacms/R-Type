/*
** EPITECH PROJECT, 2023
** src
** File description:
** Manager
*/

#include <csignal>
#include <iostream>
#include <memory>
#include <ostream>
#include <rtype.hh>
#include <rtype/Manager.hh>
#include <rtype/network/Network.hh>

static volatile std::atomic_int RUNNING = 1;

/* constructors and destructors */

/**
 * @brief Default constructor
 *
 * @param port port_type, default to 8080
 */
rserver::Manager::Manager(asio::ip::port_type port)
    : socket{this->context, asio::ip::udp::endpoint{asio::ip::udp::v4(), port}}
{
    // std::signal(SIGINT, Manager::handle_disconnection);
}

rserver::Manager::Manager(rserver::Manager &&to_move) : socket{std::move(to_move.socket)}
{
}

rserver::Manager::~Manager()
{
    this->threads.stop();
    std::cout << "bye" << ENDL;
}

/* operator overload */

rserver::Manager &rserver::Manager::operator=(Manager &&to_move)
{
    this->socket = std::move(to_move.socket);

    return *this;
}

/* methods */
void rserver::Manager::launch(asio::ip::port_type port)
{
    try {
        Manager manager{port};

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

void rserver::Manager::start_receive()
{
    ntw::Communication communication{};

    if (RUNNING) {
        this->socket.async_receive_from(asio::buffer(&communication, sizeof(communication)),
                                        this->endpoint, [this](auto &&p_h1, auto &&p_h2) {
                                            handle_receive(std::forward<decltype(p_h1)>(p_h1),
                                                           std::forward<decltype(p_h2)>(p_h2));
                                        });
        if (this->endpoint.port() > 0)
            this->threads.add_job([&, this]() { this->command_manager(communication, endpoint); });
    }
}

void rserver::Manager::handle_receive(const asio::error_code &error,
                                      std::size_t /* bytes_transferre */)
{
    ntw::Communication communication{};

    if (!error && RUNNING) {
        this->socket.async_send_to(asio::buffer(&communication, sizeof(communication)),
                                   this->endpoint, [this, communication](auto &&p_h1, auto &&p_h2) {
                                       handle_send(communication,
                                                   std::forward<decltype(p_h1)>(p_h1),
                                                   std::forward<decltype(p_h2)>(p_h2));
                                   });
        this->start_receive();
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
    // TODO parse command arguments
    // loop through commands and go to method pointers
    // TODO also check if client is new or not
    std::cout << "oue " << client << "\n";
}

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
