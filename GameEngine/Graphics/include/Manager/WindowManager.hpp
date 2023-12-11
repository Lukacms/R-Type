#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

enum class GameEvent {
    Close,
    KeyPress,
    MouseClick,
};

class WindowManager {
private:
    sf::RenderWindow window;
    std::unordered_map<GameEvent, std::function<void()>> eventCallbacks;

public:
    WindowManager();
    ~WindowManager();

    void createWindow(int width, int height, const std::string& title);
    sf::RenderWindow& getWindow();
    void closeWindow();
    void clear();
    void display();
    bool isWindowOpen() const;
    void pollEvents();
    void onEvent(GameEvent event, std::function<void()> callback);
};
