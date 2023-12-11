/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sceneManager
*/

#include <rtype/SceneManager.hpp>

SceneManager::SceneManager() : currentScene(nullptr) {
}

void SceneManager::addScene(const std::string& name, std::shared_ptr<Scene> scene) {
    scenes[name] = scene;
}

void SceneManager::removeScene(const std::string& name) {
    scenes.erase(name);
}

void SceneManager::changeScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        currentScene = it->second;
        currentScene->init();
    }
}

void SceneManager::updateCurrentScene(float dt) {
    if (currentScene) {
        currentScene->update(dt);
    }
}

void SceneManager::drawCurrentScene(sf::RenderWindow& window) {
    if (currentScene) {
        currentScene->draw(window);
    }
}
