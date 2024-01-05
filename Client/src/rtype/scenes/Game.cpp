/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Game
*/

#include <rtype/Client.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/network/Network.hpp>
#include <rtype/scenes/Game.hh>

rclient::scenes::Game::Game(asio::ip::udp::endpoint &pendpoint, asio::ip::udp::socket &psocket)
    : endpoint{pendpoint}, socket{psocket}
{
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};
    rtype::SparseArray<rtype::HealthComponent> health{};

    this->ecs.get_class().register_component(sprites);
    this->ecs.get_class().register_component(transforms);
    this->ecs.get_class().register_component(tags);
    this->ecs.get_class().register_component(colliders);
    this->ecs.get_class().register_component(health);
}

void rclient::scenes::Game::display(rtype::GraphicModule &graphics)
{
    graphics.clear();
    graphics.draw_components(this->ecs.get_class().get_components<rtype::SpriteComponent>(),
                             this->ecs.get_class().get_components<rtype::TransformComponent>());
    graphics.display();
}

void rclient::scenes::Game::handle_events(rtype::GraphicModule &graphics, sf::Event & /* events */,
                                          State &state)
{
    if (graphics.is_input_pressed(sf::Keyboard::Up)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(0);
        // Client::send_message(commn);
    }
    if (graphics.is_input_pressed(sf::Keyboard::Right)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(1);
        // Client::send_message(commn);
    }
    if (graphics.is_input_pressed(sf::Keyboard::Down)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(2);
        // Client::send_message(commn);
    }
    if (graphics.is_input_pressed(sf::Keyboard::Left)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(3);
        // Client::send_message(commn);
    }
    if (graphics.is_input_pressed(sf::Keyboard::W) &&
        this->timer_shoot.get_elapsed_time_in_ms() > BULLET_TIMEOUT) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(4);
        // Client::send_message(commn);
        this->timer_shoot.reset();
    }
    if (graphics.is_input_pressed(sf::Keyboard::Escape))
        state = State::Menu;
}
