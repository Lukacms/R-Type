/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include <rtype/Client.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <iostream>

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
    m_ecs.get_class().register_component(sprites);
    m_ecs.get_class().register_component(transforms);
    m_ecs.get_class().register_component(tags);
    m_ecs.get_class().register_component(colliders);
}

int rclient::Client::client_run()
{
    while ((m_graphical_module.get_class().is_window_open())) {
        m_graphical_module.get_class().update();
        m_state == STATE::Menu ? client_menu() : client_game();
    }
    return 0;
}

void rclient::Client::client_menu()
{
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Left))
        std::cout << "TEST LEFT" << std::endl;
    // if (action in order to change the scene);
    // call configure_network();
    //m_state = STATE::Game;
}

void rclient::Client::client_game()
{
    m_network->fetch_messages();

    // if die
    // change m_state to STATE::Menu
    // destroy the networkManager
}

void rclient::Client::configure_network()
{
    m_network = std::make_unique<NetworkManager>(m_host, m_port);
    m_state = STATE::Game;
}
