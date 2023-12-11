/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** windowManager
*/

#include <Manager/WindowManager.hpp>

WindowManager::WindowManager() {
}

WindowManager::~WindowManager() {
}

void WindowManager::createWindow(int width, int height, const std::string& title) {
    window.create(sf::VideoMode(width, height), title);
}

sf::RenderWindow& WindowManager::getWindow() {
    return window;
}

void WindowManager::closeWindow() {
    window.close();
}

void WindowManager::clear() {
    window.clear();
}

void WindowManager::display() {
    window.display();
}

bool WindowManager::isWindowOpen() const {
    return window.isOpen();
}

void WindowManager::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                if (eventCallbacks.count(GameEvent::Close)) eventCallbacks[GameEvent::Close]();
                break;
        }
    }
}

void WindowManager::onEvent(GameEvent event, std::function<void()> callback) {
    eventCallbacks[event] = callback;
}
