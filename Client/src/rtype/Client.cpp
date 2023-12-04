/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#include <rtype/Client.hpp>

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

void rclient::Client::update()
{
    m_movement_system.update(m_registry);
    m_transform_system.update(m_registry);
    m_sprite_system.update(m_registry);
}

void rclient::Client::render()
{
    m_window->clear(sf::Color::Black);
    m_sprite_system.render(m_registry, m_window);
    m_window->display();
}

Registry &rclient::Client::get_registry()
{
    return m_registry;
}
