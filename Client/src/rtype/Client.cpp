/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Client
*/

#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <csignal>
#include <iostream>
#include <rtype.hh>
#include <rtype/Client.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>
#include <vector>

/* handle <CTRL-C> */
static volatile std::atomic_int RUNNING{1};

static void handle_sigint(int /* unused */)
{
    RUNNING = 0;
}

/* ctor / dtor */
rclient::Client::Client(const rclient::Arguments &infos)
    : resolver{this->context}, socket{this->context}, game{endpoint, socket},
      host{std::move(infos.hostname)}, port{std::move(infos.port)}
{
    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    graphics.init_class<std::unique_ptr<rtype::GraphicModule>(
        unsigned int width, unsigned int height, const std::string &title)>(
        "./libs/r-type-graphics.so", "entrypoint", scenes::STANDARD_WIDTH, scenes::STANDARD_HEIGHT,
        STANDARD_TITLE.data());
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};
    rtype::SparseArray<rtype::HealthComponent> health{};

    ecs.get_class().register_component(sprites);
    ecs.get_class().register_component(transforms);
    ecs.get_class().register_component(tags);
    ecs.get_class().register_component(colliders);
    ecs.get_class().register_component(health);
    std::signal(SIGINT, &handle_sigint);
}

rclient::Client::~Client()
{
    RUNNING = 0;
    Client::send_message({}, this->endpoint, this->socket);
    if (this->graphics.get_class().is_window_open()) {
        this->graphics.get_class().close_window();
    }
    this->threads.stop();
    DEBUG(("Stopping client%s", ENDL));
}

rclient::Client::Client(rclient::Client &&to_move)
    : resolver{std::move(to_move.resolver)}, socket{std::move(to_move.socket)},
      game{std::move(to_move.game)}, threads{std::move(to_move.threads)},
      host{std::move(to_move.host)}, port{std::move(to_move.port)}
{
}

/* methods */

/* static */
void rclient::Client::send_message(const ntw::Communication &commn,
                                   const asio::ip::udp::endpoint &endpoint,
                                   asio::ip::udp::socket &socket)
{
    socket.send_to(asio::buffer(&commn, sizeof(commn)), endpoint);
}

int rclient::Client::launch(const Arguments &infos)
{
    Client client{infos};

    client.loop();
    return SUCCESS;
}

/**
 * @brief Setup network for the rest of the game.
 * Should be executed after Menu
 */
void rclient::Client::setup_network()
{
    std::cout << "oui\n";
    this->state = scenes::State::Game;
    this->endpoint = *this->resolver.resolve(asio::ip::udp::v4(), this->host, this->port).begin();
    this->socket.open(asio::ip::udp::v4());
    this->socket.non_blocking(true); // <- set socket mode as non-blocking
    Client::send_message({ntw::NetworkType::Connection}, this->endpoint, this->socket);
    this->threads.add_job([&, this]() -> void {
        ntw::Communication commn{};
        asio::ip::udp::endpoint sender{};

        while (RUNNING) {
            try {
                this->socket.receive_from(asio::buffer(&commn, sizeof(commn)), sender);
                if (sender.port() > 0) {
                    // TODO handle messages
                }
            } catch (std::exception & /* e */) {
            }
        }
    });
}

void rclient::Client::loop()
{
    rtype::utils::Clock clock{};

    while (RUNNING) {
        if (clock.get_elapsed_time_in_ms() > GAME_TIMEOUT) {
            this->launch_displays();
            clock.reset();
        }
        this->check_events();
    }
}

void rclient::Client::launch_displays()
{
    switch (this->state) {
        case scenes::State::Menu:
            return this->menu.display(this->graphics.get_class());
        case scenes::State::Lounge:
            return this->lounge.display(this->graphics.get_class());
        case scenes::State::Game:
            return this->game.display(this->graphics.get_class());
        case scenes::State::Pause:
            return this->pause.display(this->graphics.get_class());
    }
}

void rclient::Client::check_events()
{
    sf::Event event{};

    while (this->graphics.get_class().poll_event(event)) {
        if (this->state == scenes::State::Menu && event.key.code == sf::Keyboard::Enter) {
            this->setup_network();
        }
        if (this->graphics.get_class().is_input_pressed(sf::Keyboard::Q))
            RUNNING = 0;
        switch (this->state) {
            case scenes::State::Menu:
                this->menu.handle_events(this->graphics.get_class(), event, this->state);
                break;
            case scenes::State::Lounge:
                this->lounge.handle_events(this->graphics.get_class(), event, this->state);
                break;
            case scenes::State::Game:
                this->game.handle_events(this->graphics.get_class(), event, this->state);
                break;
            case scenes::State::Pause:
                this->pause.handle_events(this->graphics.get_class(), event, this->state);
                break;
        }
    }
}
