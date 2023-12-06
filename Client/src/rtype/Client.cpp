/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include <rtype/Client.hpp>
#include <rtype/Components/SpriteComponent.hh>

rclient::Client::Client(u_int width, u_int height)
{
    sf::VideoMode video_mode{width, height};
    m_window = std::make_unique<sf::RenderWindow>(video_mode, WINDOW_NAME, WINDOW_STYLE);
}

bool rclient::Client::is_running()
{
    return m_window->isOpen();
}

void rclient::Client::read_input()
{
    sf::Event evt{};

    while (m_window->pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

void rclient::Client::render(rtype::ECSManager &manager)
{
    auto sprites = manager.get_components<SpriteComponent>();

    m_window->clear();
    for (auto &sprite : sprites)
        if (sprite.has_value())
            m_window->draw(sprite->sprite);
    m_window->display();
}
