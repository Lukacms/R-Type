/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Client
*/

#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <csignal>
#include <rtype.hh>
#include <rtype/Client.hh>
#include <rtype/Components/AnimationComponent.hh>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/HealthComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/SFML/SFMLGraphicModule.hh>
#include <rtype/scenes/IScene.hh>
#include <rtype/utils/Clock.hh>
#include <vector>

/* handle <CTRL-C> */
static volatile std::atomic_int RUNNING{1};

/**
 * @brief Signal function to have a clean quit
 */
static void handle_sigint(int /* unused */)
{
    RUNNING = 0;
}

/* ctor / dtor */
/**
 * @brief Constructor for Client class. Init dlloaded classes, and everything needed
 *
 * @param infos - Arguments &
 */
rclient::Client::Client(const rclient::Arguments &infos)
    : resolver{this->context}, socket{this->context}, lounge{this->socket, this->endpoint},
      game{this->endpoint, this->socket}, host{std::move(infos.hostname)},
      port{std::move(infos.port)}
{
    try {
#ifdef __linux
        this->graphics.init_class<std::unique_ptr<rtype::IGraphicModule>(
            unsigned int width, unsigned int height, const std::string &title)>(
            "./libs/r-type-graphics.so", "entrypoint", rtype::STANDARD_WIDTH,
            rtype::STANDARD_HEIGHT, STANDARD_TITLE.data());
        this->audio.init_class<std::unique_ptr<rtype::IAudioModule>()>("./libs/r-type-audio.so",
                                                                       "entrypoint");
#else
        this->graphics
            .init_class<void *(unsigned int width, unsigned int height, const std::string &title)>(
                "./libs/r-type-graphics.so", "entrypoint", rtype::STANDARD_WIDTH,
                rtype::STANDARD_HEIGHT, STANDARD_TITLE.data());
        this->audio.init_class<void *()>("./libs/r-type-audio.so", "entrypoint");
#endif /* __linux */
    } catch (rtype::AudioModuleException &e) {
        throw Client::ClientException("Audio Module cannot be loaded");
    }
    std::signal(SIGINT, &handle_sigint);
}

/**
 * @brief Destructor for Client class
 */
rclient::Client::~Client()
{
    RUNNING = 0;
    Client::send_message({ntw::NetworkType::End}, this->endpoint, this->socket);
    if (this->graphics.get_class().is_window_open()) {
        this->graphics.get_class().close_window();
    }
    this->threads.stop();
    DEBUG(("Stopping client%s", ENDL));
}

/**
 * @brief Move constructor for client's class
 *
 * @param to_move - Client &&
 */
rclient::Client::Client(rclient::Client &&to_move)
    : resolver{std::move(to_move.resolver)}, socket{std::move(to_move.socket)},
      lounge{to_move.socket, to_move.endpoint}, game{to_move.endpoint, to_move.socket},
      threads{std::move(to_move.threads)}, host{std::move(to_move.host)},
      port{std::move(to_move.port)}
{
}

/* static */
/**
 * @brief Send a message to the server
 *
 * @param commn - const Communication &
 * @param endpoint - const asio::udp::endpoint &
 * @param socket - asio::udp::socket &
 */
void rclient::Client::send_message(const ntw::Communication &commn,
                                   const asio::ip::udp::endpoint &endpoint,
                                   asio::ip::udp::socket &socket)
{
    if (socket.is_open())
        socket.send_to(asio::buffer(&commn, sizeof(commn)), endpoint);
}

/**
 * @brief static method to create and launch client graphics, first on Menu scene
 *
 * @param infos - const Arguments &
 * @return - int
 */
int rclient::Client::launch(const Arguments &infos)
{
    try {
        Client client{infos};
        client.loop();
        return SUCCESS;
    } catch (rtype::AudioModuleException &e) {
        throw ClientException("Audio module cannot be load\n");
    }
}

/* methods */

/**
 * @brief Setup network for the rest of the game.
 * Should be executed after Menu
 */
void rclient::Client::setup_network()
{
    this->state = scenes::State::Lounge;
    this->endpoint = *this->resolver.resolve(asio::ip::udp::v4(), this->host, this->port).begin();
    this->socket.open(asio::ip::udp::v4());
    this->socket.non_blocking(true); // <- set socket mode as non-blocking
    Client::send_message({ntw::NetworkType::Connection}, this->endpoint, this->socket);

    this->threads.add_job([&, this]() -> void {
        ntw::Communication commn{};
        asio::ip::udp::endpoint sender{};

        while (RUNNING && this->state != scenes::State::End) {
            {
                std::unique_lock<std::shared_mutex> lock{this->graphics_lock};
                if (!this->graphics.get_class().is_window_open())
                    break;
            }
            try {
                std::unique_lock<std::shared_mutex> lock{this->audio_lock};
                this->socket.receive_from(asio::buffer(&commn, sizeof(commn)), sender);
                if (sender.port() > 0) {
                    switch (this->state) {
                        case scenes::State::Game:
                            this->game.handle_network(commn, this->audio.get_class(), this->state);
                            break;
                        case scenes::State::Lounge:
                            this->lounge.handle_network(commn, this->audio.get_class(),
                                                        this->state);
                            break;
                        case scenes::State::Pause:
                            this->game.handle_network(commn, this->audio.get_class(), this->state);
                            break;
                        case scenes::State::Menu:
                            break;
                        case scenes::State::End:
                            break;
                    }
                }
            } catch (std::exception & /* e */) {
            }
        }
    });
}

/**
 * @brief Client's loop, launches display, handle network and events
 */
void rclient::Client::loop()
{
    rtype::utils::Clock clock{};

    this->audio.get_class().play_music("TitleScreen");
    while (RUNNING && this->state != scenes::State::End) {
        {
            std::unique_lock<std::shared_mutex> lock{this->graphics_lock};
            if (!this->graphics.get_class().is_window_open())
                return;
        }
        this->graphics.get_class().update();
        {
            std::unique_lock<std::shared_mutex> lock{this->audio_lock};
            this->audio.get_class().update();
        }
        if (clock.get_elapsed_time_in_ms() > GAME_TIMEOUT) {
            this->launch_displays();
            clock.reset();
        }
        this->check_events();
    }
}

/**
 * @brief Launches all displays depending on Scene enum
 */
void rclient::Client::launch_displays()
{
    std::unique_lock<std::shared_mutex> lock{this->scenes};
    std::unique_lock<std::shared_mutex> g_lock{this->graphics_lock};
    switch (this->state) {
        case scenes::State::Menu:
            return this->menu.display(this->graphics.get_class());
        case scenes::State::Lounge:
            return this->lounge.display(this->graphics.get_class());
        case scenes::State::Game:
            return this->game.display(this->graphics.get_class());
        case scenes::State::Pause:
            return this->pause.display(this->graphics.get_class());
        case scenes::State::End:
            return;
    }
}

/**
 * @brief check if there were any events, and handle them, here on in state's function
 */
void rclient::Client::check_events()
{

    std::unique_lock<std::shared_mutex> g_lock{this->graphics_lock};
    std::unique_lock<std::shared_mutex> a_lock{this->audio_lock};
    if (this->state == scenes::State::Menu &&
        this->graphics.get_class().is_input_pressed(rtype::Keys::ENTER)) {
        this->setup_network();
    }
    if (this->graphics.get_class().is_input_pressed(rtype::Keys::Q))
        RUNNING = 0;
    switch (this->state) {
        case scenes::State::Menu:
            this->menu.handle_events(this->graphics.get_class(), this->audio.get_class(),
                                     this->state);
            break;
        case scenes::State::Lounge:
            this->lounge.handle_events(this->graphics.get_class(), this->audio.get_class(),
                                       this->state);
            break;
        case scenes::State::Game:
            this->game.handle_events(this->graphics.get_class(), this->audio.get_class(),
                                     this->state);
            break;
        case scenes::State::Pause:
            this->pause.handle_events(this->graphics.get_class(), this->audio.get_class(),
                                      this->state);
            break;
        case scenes::State::End:
            return;
    }
}

rclient::Client::ClientException::ClientException(std::string &&perror_msg)
{
    m_error_msg = perror_msg;
}

const char *rclient::Client::ClientException::what() const noexcept
{
    return m_error_msg.c_str();
}
