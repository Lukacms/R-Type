/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** networkManager.cpp
*/

#include <asio/buffer.hpp>
#include <iostream>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Factory/ClientEntityFactory.hh>
#include <rtype/Network/NetworkManager.hh>
#include <rtype/network/Network.hpp>

using asio::ip::udp;

static const std::vector<rclient::CommandHandler> HANDLER{
    {ntw::Entity, {rclient::NetworkManager::manage_entity}},
    {ntw::Destruction, {rclient::NetworkManager::delete_entity}},
    {ntw::Position, {rclient::NetworkManager::move_entity}},
    {ntw::End, {rclient::NetworkManager::end_game}},
};

rclient::NetworkManager::NetworkManager(const std::string &host, const std::string &port)
    : m_resolver{m_io_context},
      m_receiver_endpoint{*(m_resolver.resolve(asio::ip::udp::v4(), host, port).begin())},
      m_socket{m_io_context}
{
    m_receiver_endpoint = *m_resolver.resolve(asio::ip::udp::v4(), host, port).begin();
    m_socket.open(udp::v4());
    ntw::Communication commn{.type = ntw::NetworkType::Connection, .args = {}};

    this->send_message(commn);
    this->m_io_context.run();
}

void rclient::NetworkManager::fetch_messages()
{
    ntw::Communication comm{};
    asio::ip::udp::endpoint sender_endpoint;

    m_socket.async_receive_from(asio::buffer(&comm, sizeof(comm)), sender_endpoint,
                                [this](auto &&p_1, auto &&p_2) { this->handle_receive(p_1, p_2); });
    if (sender_endpoint.port() > 0)
        m_queue.emplace_back(comm);
}

void rclient::NetworkManager::handle_receive(const asio::error_code &error,
                                             std::size_t bytes_transferred)
{
    if (!error) {
        this->fetch_messages();
    }
}

void rclient::NetworkManager::send_message(ntw::Communication &communication)
{
    m_socket.async_send_to(asio::buffer(&communication, sizeof(communication)), m_receiver_endpoint,
                           [](auto && /* p_1 */, auto && /* p_2 */) {});
}

std::deque<ntw::Communication> &rclient::NetworkManager::get_message_queue()
{
    return m_queue;
}

void rclient::NetworkManager::manage_message(rtype::ECSManager &manager)
{
    ntw::Communication new_message{};

    while (!m_queue.empty()) {
        new_message = m_queue.front();
        for (CommandHandler f_ptr : HANDLER)
            if (f_ptr.type == new_message.type)
                f_ptr.handler(*this, manager, new_message);
        m_queue.pop_front();
    }
}

void rclient::NetworkManager::create_entity(
    rclient::NetworkManager &network_manager __attribute_maybe_unused__,
    rtype::ECSManager &ecs_manager, ntw::Communication &communication)
{
    std::vector<std::string> arguments = communication.deserialize();
    rclient::ClientEntityFactory::create(static_cast<size_t>(std::stoi(arguments[0])), arguments[1],
                                         ecs_manager);
}

void rclient::NetworkManager::move_entity(
    rclient::NetworkManager &network_manager __attribute_maybe_unused__,
    rtype::ECSManager &ecs_manager, ntw::Communication &communication)
{
    std::vector<std::string> arguments = communication.deserialize();
    auto &transform = ecs_manager.get_component<rtype::TransformComponent>(
        static_cast<size_t>(std::stoi(arguments[0])));
    transform.position_x = static_cast<float>(std::stof(arguments[2]));
    transform.position_y = static_cast<float>(std::stof(arguments[3]));
}

void rclient::NetworkManager::end_game(rclient::NetworkManager & /* network_manager */,
                                       rtype::ECSManager & /* ecs_manager */,
                                       ntw::Communication & /* communication */)
{
    // Find how to pass the game State;
}

void rclient::NetworkManager::delete_entity(
    rclient::NetworkManager &network_manager __attribute_maybe_unused__,
    rtype::ECSManager &ecs_manager, ntw::Communication &communication)
{
    std::vector<std::string> arguments = communication.deserialize();
    ecs_manager.delete_entity(static_cast<size_t>(std::stoi(arguments[0])));
}

void rclient::NetworkManager::manage_entity(rclient::NetworkManager &network_manager,
                                            rtype::ECSManager &ecs_manager,
                                            ntw::Communication &communication)
{
    std::vector<std::string> arguments = communication.deserialize();

    if (!ecs_manager.is_entity_used(std::stoul(arguments[0])))
        rclient::NetworkManager::create_entity(network_manager, ecs_manager, communication);
    rclient::NetworkManager::move_entity(network_manager, ecs_manager, communication);
}
