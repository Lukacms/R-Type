/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** client
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <rtype/ComponentManager.hpp>
#include <rtype/ECSManager.hpp>

namespace rclient
{
    constexpr const u_int STANDARD_WIDTH{800};
    constexpr const u_int STANDARD_HEIGHT{600};
    constexpr const std::string WINDOW_NAME{"R-TYPE"};
    constexpr const u_int32_t WINDOW_STYLE{sf::Style::Resize | sf::Style::Close};

    class Client
    {
        public:
            explicit Client(u_int width = STANDARD_WIDTH, u_int height = STANDARD_HEIGHT);
            ~Client() = default;
            Client(const Client &) = delete;
            Client(Client &&) = delete;
            Client &operator=(const Client &) = delete;
            Client &operator=(Client &&) = delete;

            bool is_running();
            void read_input();
            void render(rtype::ECSManager &manager);

        private:
            size_t m_width{STANDARD_WIDTH};
            size_t m_height{STANDARD_HEIGHT};
            std::unique_ptr<sf::RenderWindow> m_window;
    };
} // namespace rclient
