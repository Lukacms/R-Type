/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include <rtype/Client.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>

rclient::Client::Client(unsigned int width, unsigned int height, const std::string &title)
{
    m_ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    m_graphical_module.init_class<std::unique_ptr<rtype::GraphicModule>(
        unsigned int width, unsigned int height, const std::string &title)>(
        "./libs/r-type-graphics.so", "entrypoint", width, height, title);
    SparseArray<rtype::SpriteComponent> sprites{};
    SparseArray<rtype::TransformComponent> transforms{};
    SparseArray<rtype::TagComponent> tags{};
    SparseArray<rtype::BoxColliderComponent> colliders{};
    SparseArray<rtype::HealthComponent> health{};
    m_ecs.get_class().register_component(sprites);
    m_ecs.get_class().register_component(transforms);
    m_ecs.get_class().register_component(tags);
    m_ecs.get_class().register_component(colliders);
    m_ecs.get_class().register_component(health);
}

int rclient::Client::client_run()
{
    while ((m_graphical_module.get_class().is_window_open())) {
        m_graphical_module.get_class().update();
        m_state == STATE::Menu ? client_menu() : client_game();
        m_graphical_module.get_class().clear();
        m_graphical_module.get_class().draw_components(
            m_ecs.get_class().get_components<rtype::SpriteComponent>(),
            m_ecs.get_class().get_components<rtype::TransformComponent>());
        m_graphical_module.get_class().display();
    }
    return 0;
}

void rclient::Client::client_menu()
{
    // if (action in order to change the scene);
    m_host = "0.0.0.0";
    m_port = "8080";
    configure_network();
}

void rclient::Client::client_game()
{
    m_network->fetch_messages();
    m_network->manage_message(m_ecs.get_class());
    check_input();
    send_client_input();
}

void rclient::Client::configure_network()
{
    ntw::Communication connection{};

    connection.type = ntw::Connection;
    m_network = std::make_unique<NetworkManager>(m_host, m_port);
    m_network->send_message(connection);
    m_state = STATE::Game;
}

void rclient::Client::send_client_input()
{
    for (auto message : m_to_send) {
        m_network->send_message(message);
    }
    m_to_send.clear();
}

void rclient::Client::check_input()
{
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Up)) {
        ntw::Communication to_send{};
        to_send.type = ntw::Input;
        to_send.add_param(0);
        m_to_send.emplace_back(to_send);
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Right)) {
        ntw::Communication to_send{};
        to_send.type = ntw::Input;
        to_send.add_param(1);
        m_to_send.emplace_back(to_send);
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Down)) {
        ntw::Communication to_send{};
        to_send.type = ntw::Input;
        to_send.add_param(2);
        m_to_send.emplace_back(to_send);
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Left)) {
        ntw::Communication to_send{};
        to_send.type = ntw::Input;
        to_send.add_param(3);
        m_to_send.emplace_back(to_send);
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::W)) {
        ntw::Communication to_send{};
        to_send.type = ntw::Input;
        to_send.add_param(4);
        m_to_send.emplace_back(to_send);
    }
}
