/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include "SFML/Graphics/Sprite.hpp"
#include <array>
#include <atomic>
#include <csignal>
#include <iostream>
#include <rtype.hh>
#include <rtype/Client.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>

static volatile std::atomic_int RUNNING{1};

static void handle_sigint(int /* unused */)
{
    RUNNING = 0;
}

/* ctor / dtor */
rclient::Client::Client(unsigned int width, unsigned int height, const std::string &title)
    : m_menu{width, height}
{
    m_ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    m_graphical_module.init_class<std::unique_ptr<rtype::GraphicModule>(
        unsigned int width, unsigned int height, const std::string &title)>(
        "./libs/r-type-graphics.so", "entrypoint", width, height, title);
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};
    rtype::SparseArray<rtype::HealthComponent> health{};

    m_ecs.get_class().register_component(sprites);
    m_ecs.get_class().register_component(transforms);
    m_ecs.get_class().register_component(tags);
    m_ecs.get_class().register_component(colliders);
    m_ecs.get_class().register_component(health);
    std::signal(SIGINT, handle_sigint);
}

rclient::Client::~Client()
{
    m_network->send_message({.type = ntw::NetworkType::End, .args = {}});
    if (m_graphical_module.get_class().is_window_open()) {
        m_graphical_module.get_class().close_window();
    }
    this->threads.stop();
    DEBUG(("Stopping client%s", ENDL));
}

/* methods */
int rclient::Client::client_run()
{
    auto start = std::chrono::steady_clock::now();

    while ((m_graphical_module.get_class().is_window_open()) && RUNNING) {
        m_graphical_module.get_class().update();
        m_state == STATE::Menu ? client_menu() : client_game(start);
        m_graphical_module.get_class().clear();
        m_graphical_module.get_class().draw_components(
            m_ecs.get_class().get_components<rtype::SpriteComponent>(),
            m_ecs.get_class().get_components<rtype::TransformComponent>());
        m_graphical_module.get_class().display();
    }
    RUNNING = 0;
    return rclient::SUCCESS;
}

/**
 * @brief static method that launch client, set arguments for network and launch the game loop
 *
 * @param infos Arguments - parsed from command line, with default values
 * @return int - either SUCCESS (0) or FAILURE (84)
 */
int rclient::Client::launch(Arguments &infos)
{
    try {
        Client client{};

        client.set_network_infos(infos);
        return client.client_run();
    } catch (std::exception &e) {
        DEBUG(("%s\n", e.what()));
    }
    return SUCCESS;
}

void rclient::Client::set_network_infos(rclient::Arguments &infos)
{
    m_host = infos.hostname;
    m_port = infos.port;
}

void rclient::Client::client_menu()
{
    m_menu.launch(m_graphical_module, m_host, m_port);
    configure_network();
}

void rclient::Client::client_game(std::chrono::time_point<std::chrono::steady_clock> &start)
{
    check_input();
    if (static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::steady_clock::now() - start)
                                .count()) > GAME_TIMEOUT &&
        RUNNING) {
        start = std::chrono::steady_clock::now();
    }
}

void rclient::Client::configure_network()
{
    m_network = std::make_unique<NetworkManager>(m_host, m_port);
    m_state = STATE::Game;
    this->threads.add_job([&, this]() {
        while (RUNNING) {
            this->m_network->fetch_messages(this->m_ecs.get_class());
        }
    });
}

void rclient::Client::check_input()
{
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Up)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(0);
        this->threads.add_job([to_send, this]() { m_network->send_message(to_send); });
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Right)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(1);
        this->threads.add_job([to_send, this]() { m_network->send_message(to_send); });
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Down)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(2);
        this->threads.add_job([to_send, this]() { m_network->send_message(to_send); });
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Left)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(3);
        this->threads.add_job([to_send, this]() { m_network->send_message(to_send); });
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::W) &&
        static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::steady_clock::now() - m_timer_shoot)
                                .count()) > BULLET_TIMEOUT) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(4);
        this->threads.add_job([to_send, this]() { m_network->send_message(to_send); });
        m_timer_shoot = std::chrono::steady_clock::now();
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Escape)) {
        PauseMenu pause_menu(STANDARD_WIDTH, STANDARD_HEIGHT);
        pause_menu.launch(m_graphical_module);
    }
    if (m_graphical_module.get_class().is_input_pressed(sf::Keyboard::Q)) {
        RUNNING = 0;
    }
}
