/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sceneManager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class Scene
{
    public:
        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
};

class SceneManager
{
    public:
        SceneManager();

        void addScene(const std::string &name, std::shared_ptr<Scene> scene);
        void removeScene(const std::string &name);
        void changeScene(const std::string &name);
        void updateCurrentScene(float dt);
        void drawCurrentScene(sf::RenderWindow &window);

    private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
        std::shared_ptr<Scene> currentScene;
};
