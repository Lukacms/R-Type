/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Game
*/

#include <iostream>
#include <rtype.hh>
#include <rtype/Client.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Factory/ClientEntityFactory.hh>
#include <rtype/network/Network.hpp>
#include <rtype/scenes/Game.hh>
#include <shared_mutex>
#include <string>
#include <vector>

/**
 * @brief Handler of network events by their type event
 */
static const std::vector<rclient::scenes::CommandHandler> HANDLER{
    {ntw::NetworkType::Entity, &rclient::scenes::Game::manage_entity},
    {ntw::NetworkType::Destruction, &rclient::scenes::Game::delete_entity},
    {ntw::NetworkType::Position, &rclient::scenes::Game::move_entity},
    {ntw::NetworkType::End, &rclient::scenes::Game::end_game},
};

/**
 * @brief Constructor for Game class
 *
 * @param pendpoint - asio::udp::endpoint &
 * @param psocket - asio::udp::socket &
 */
rclient::scenes::Game::Game(asio::ip::udp::endpoint &pendpoint, asio::ip::udp::socket &psocket)
    : endpoint{pendpoint}, socket{psocket}
{
#ifdef __linux
    this->ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
#else
    this->ecs.init_class<void *()>("./libs/r-type-ecs.so");
#endif /* __linux */
    rtype::SparseArray<rtype::SpriteComponent> sprites{};
    rtype::SparseArray<rtype::TransformComponent> transforms{};
    rtype::SparseArray<rtype::TagComponent> tags{};
    rtype::SparseArray<rtype::BoxColliderComponent> colliders{};
    rtype::SparseArray<rtype::HealthComponent> health{};
    rtype::SparseArray<rtype::AnimationComponent> animation{};
    std::function<void(rtype::ComponentManager &, float)> animation_system{
        &rtype::animation_system};

    this->ecs.get_class().register_component(sprites);
    this->ecs.get_class().register_component(transforms);
    this->ecs.get_class().register_component(tags);
    this->ecs.get_class().register_component(colliders);
    this->ecs.get_class().register_component(health);
    this->ecs.get_class().register_component(animation);
    this->ecs.get_class().add_system(animation_system);
}

/**
 * @brief Override function of IScene, to display elements to graphical window
 *
 * @param graphics - IGraphicModule &
 */
void rclient::scenes::Game::display(rtype::IGraphicModule &graphics)
{
    graphics.clear();
    ecs.get_class().apply_system(0);
    this->background_manager.update();
    for (auto &cbg : this->background_manager.get_backgrounds())
        graphics.draw(cbg.sprite, cbg.transform);
    graphics.draw_components(this->ecs.get_class().get_components<rtype::SpriteComponent>(),
                             this->ecs.get_class().get_components<rtype::TransformComponent>());
    graphics.display();
}

/**
 * @brief Override function of IScene. Handle events recieved from the user
 *
 * @param graphics - IGraphicModule &
 * @param audio - IAudioModule &
 * @param state - State &
 */
void rclient::scenes::Game::handle_events(rtype::IGraphicModule &graphics,
                                          rtype::IAudioModule &audio, State &state)
{
    if (graphics.is_input_pressed(rtype::Keys::UP)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(0);
        Client::send_message(to_send, this->endpoint, this->socket);
    }
    if (graphics.is_input_pressed(rtype::Keys::RIGHT)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(1);
        Client::send_message(to_send, this->endpoint, this->socket);
    }
    if (graphics.is_input_pressed(rtype::Keys::DOWN)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(2);
        Client::send_message(to_send, this->endpoint, this->socket);
    }
    if (graphics.is_input_pressed(rtype::Keys::LEFT)) {
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(3);
        Client::send_message(to_send, this->endpoint, this->socket);
    }
    if (graphics.is_input_pressed(rtype::Keys::W) &&
        this->timer_shoot.get_elapsed_time_in_ms() > BULLET_TIMEOUT) {
        audio.play_sfx("Shoot");
        ntw::Communication to_send{};
        to_send.type = ntw::NetworkType::Input;
        to_send.add_param(4);
        Client::send_message(to_send, this->endpoint, this->socket);
        this->timer_shoot.reset();
    }
    if (graphics.is_input_pressed(rtype::Keys::ESCAPE))
        state = State::Pause;
}

/**
 * @brief Handle network function. Override of IScene, launches function pointer to handlers
 *
 * @param commn - Communication &
 * @param audio - IAudioModule &
 * @param state - State &
 */
void rclient::scenes::Game::handle_network(ntw::Communication &commn, rtype::IAudioModule &audio,
                                           State &state)
{
    for (const auto &handler : HANDLER) {
        if (commn.type == ntw::NetworkType::Music)
            return this->change_music(commn, audio);
        if (commn.type == ntw::NetworkType::Background)
            return this->change_background(commn);
        if (handler.type == commn.type)
            return handler.handler(*this, commn, state);
    }
}

/* network functions */
/**
 * @brief Delete an entity
 *
 * @param commn - Communication &
 */
void rclient::scenes::Game::delete_entity(ntw::Communication &commn, State & /* state */)
{
    // std::unique_lock<std::shared_mutex> lock{this->ecs_mutex};
    std::vector<std::string> arguments = commn.deserialize();

    this->ecs.get_class().delete_entity(static_cast<size_t>(std::stoi(arguments[0])));
}

/**
 * @brief Manage an entity: create it if needed, then move it.
 *
 * @param commn - Communication &
 * @param state - State &
 */
void rclient::scenes::Game::manage_entity(ntw::Communication &commn, State &state)
{
    std::vector<std::string> arguments = commn.deserialize();

    {
        std::shared_lock<std::shared_mutex> lock{this->ecs_mutex};
        if (!this->ecs.get_class().is_entity_used(std::stoul(arguments[0])))
            this->create_entity(commn, state);
        this->move_entity(commn, state);
    }
    // DEBUG(("New X: %s, New Y: %s%s", arguments[2].c_str(), arguments[3].c_str(), ENDL));
}

/**
 * @brief Create a new entity with the ecs and ClientEntityFactory
 *
 * @param commn - Communication &
 */
void rclient::scenes::Game::create_entity(ntw::Communication &commn, State & /* state */)
{
    std::vector<std::string> arguments = commn.deserialize();

    rclient::ClientEntityFactory::create(static_cast<size_t>(std::stoi(arguments[0])), arguments[1],
                                         this->ecs.get_class());
}

/**
 * @brief Move an entity with a TransformComponent
 *
 * @param commn - Communication &
 */
void rclient::scenes::Game::move_entity(ntw::Communication &commn, State & /* state */)
{
    std::vector<std::string> arguments{commn.deserialize()};
    auto &transform = this->ecs.get_class().get_component<rtype::TransformComponent>(
        static_cast<size_t>(std::stoi(arguments[0])));

    transform.position_x = std::stof(arguments[2]);
    transform.position_y = std::stof(arguments[3]);
    transform.rotation = std::stof(arguments[4]);
}

/**
 * @brief Finish game and close client
 *
 * @param state - State &
 */
void rclient::scenes::Game::end_game(ntw::Communication & /* commn */, State &state) // NOLINT
{
    state = State::End;
}

/**
 * @brief Change music to the one given
 *
 * @param commn - Communication &
 * @param audio - IAudioModule &
 */
void rclient::scenes::Game::change_music(ntw::Communication &commn, // NOLINT
                                         rtype::IAudioModule &audio)
{
    std::vector<std::string> arguments = commn.deserialize();
    audio.play_music(arguments[0]);
}

/**
 * @brief Change the background to the one given by the server
 *
 * @param commn - Communication
 */
void rclient::scenes::Game::change_background(ntw::Communication commn)
{
    std::vector<std::string> arguments = commn.deserialize();
    background_manager.change_background(arguments[0]);
}
