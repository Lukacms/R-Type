#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

namespace rclient
{

    const constexpr int STANDARD_WIDTH{800};
    const constexpr int STANDARD_HEIGHT{800};
    const constexpr char *STANDARD_TITLE{"R-TYPE"};

    class WindowManager
    {
        public:
            WindowManager(int width = STANDARD_WIDTH, int height = STANDARD_HEIGHT,
                          const std::string &title = STANDARD_TITLE);
            ~WindowManager() = default;
            WindowManager(const WindowManager &) = delete;
            WindowManager(WindowManager &&) = delete;
            WindowManager &operator=(const WindowManager &) = delete;
            WindowManager &operator=(WindowManager &&) = delete;

            sf::RenderWindow &getWindow();
            void closeWindow();
            void clear();
            void display();
            bool isWindowOpen() const;
            void pollEvents();

        private:
            sf::VideoMode m_mode;
            sf::RenderWindow m_window;
    };
} // namespace rclient
