/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** networkManager.cpp
*/

#include <iostream>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/Network/NetworkManager.hh>

using asio::ip::udp;

static const std::vector<rclient::CommandHandler> HANDLER{
    {ntw::Creation, {rclient::NetworkManager::create_entity}},
    {ntw::Destruction, {rclient::NetworkManager::delete_entity}},
    {ntw::Position, {rclient::NetworkManager::move_entity}},
    {ntw::End, {rclient::NetworkManager::end_game}},
};

rclient::NetworkManager::NetworkManager(const std::string &host, const std::string &port)
    : m_resolver(m_io_context),
      m_receiver_endpoint(*m_resolver.resolve(asio::ip::udp::v4(), host, port).begin()),
      m_socket(m_io_context, asio::ip::udp::v4())
{
}

void rclient::NetworkManager::fetch_messages()
{
    while (m_socket.available() > 0) {
        ntw::Communication comm{};
        asio::ip::udp::endpoint sender_endpoint;
        m_socket.receive_from(asio::buffer(&comm, sizeof(comm)), sender_endpoint);
        m_queue.emplace_back(comm);
    }
}

void rclient::NetworkManager::send_message(ntw::Communication &communication)
{
    if (m_socket.available() < 0)
        return;
    m_socket.async_send_to(asio::buffer(&communication, sizeof(communication)), m_receiver_endpoint,
                           [](auto && /* p_h1 */, auto && /* p_h2 */) {});
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
    // Call Factory with ECS etc
}

void rclient::NetworkManager::move_entity(
    rclient::NetworkManager &network_manager __attribute_maybe_unused__,
    rtype::ECSManager &ecs_manager, ntw::Communication &communication)
{
    std::vector<std::string> arguments = communication.deserialize();
    auto &transform = ecs_manager.get_component<rtype::TransformComponent>(
        static_cast<size_t>(std::stoi(arguments[0])));
    transform.position_x = static_cast<float>(std::stof(arguments[1]));
    transform.position_y = static_cast<float>(std::stof(arguments[2]));
}

void rclient::NetworkManager::end_game(rclient::NetworkManager &network_manager,
                                       rtype::ECSManager &ecs_manager,
                                       ntw::Communication &communication)
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
