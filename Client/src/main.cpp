/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/
/*
<<<<<<< Updated upstream
#include <asio.hpp>
#include <iostream>
#include <iterator>
#include <rtype.hh>
#include <rtype/network/Network.hh>
#include <unistd.h>

using asio::ip::udp;

int main(int argc, char *argv[])
{
    ntw::Communication communication{};

    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        asio::io_context io_context;
        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint =
            *resolver.resolve(udp::v4(), "127.0.0.1", argv[1]).begin();
        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {'k'};
        socket.send_to(asio::buffer(send_buf, 1), receiver_endpoint);
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(asio::buffer(&communication, sizeof(communication)),
                                         receiver_endpoint);

        std::cout << (communication.type == ntw::Start ? "oui\n" : "non\n");
        std::cout << "String address: " << &communication.args << std::endl;
        std::cout << "String length: " << communication.args.size() << std::endl;
        std::cout << "String content: " << communication.args.data() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

=======
*/
#include <chrono>
#include <rtype/AudioManager.hpp>
#include <rtype/Client.hpp>
#include <rtype/Components/BoxColliderComponent.hh>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <rtype/SpriteManager.hpp>
#include <rtype/TextureManager.hpp>
#include <rtype/WindowManager.hpp>

void menu()
{
    AudioManager audio_system{};
    TextureManager texture_system{};
    SpriteManager sprite_system{};
    rclient::Client le_client{};
    rtype::ECSManager manager{};
    SparseArray<rtype::SpriteComponent> sprites{};
    SparseArray<rtype::TransformComponent> transforms{};
    SparseArray<rtype::TagComponent> tags{};
    SparseArray<rtype::BoxColliderComponent> colliders{};
    sprite_system.loadTexture("BG", "./Client/assets/backgrounds/024.png");

    audio_system.loadSound("test", "./Client/assets/sounds/Spider-Dance.wav");
    audio_system.playSound("test");

    Entity background{manager.create_entity()};
    sprites.emplace_at(background, sprite_system.createSprite("BGSprite", "BG"),
                       sf::Rect<int>{0, 0, 800, 600});
    transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);

    manager.register_component(sprites);
    manager.register_component(tags);
    manager.register_component(transforms);
    manager.register_component(colliders);
    std::function<void(ComponentManager &, float)> transform = &rtype::transform_system;
    std::function<void(ComponentManager &, float)> movement = &rtype::movement_system;
    std::function<void(ComponentManager &, float)> sprite = &rtype::sprite_system;
    std::function<void(ComponentManager &, float)> collider = &rtype::collider_system;
    manager.add_system(transform);
    manager.add_system(movement);
    manager.add_system(sprite);
    float delta_time = 0.F;
    while (le_client.is_running()) {
        auto start = std::chrono::high_resolution_clock::now();
        le_client.render(manager);
        manager.apply_system(delta_time);
        le_client.read_input();
        auto end = std::chrono::high_resolution_clock::now();
        delta_time =
            std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();
    }
}

int main(int /* argc */, const char * /* argv */[])
{
    menu();
// AudioManager audioSystem{};
//     TextureManager textureSystem{};
//     SpriteManager spriteSystem{};
//     rclient::Client le_client{};
//     rtype::ECSManager manager{};
//     SparseArray<rtype::SpriteComponent> sprites{};
//     SparseArray<rtype::TransformComponent> transforms{};
//     SparseArray<rtype::TagComponent> tags{};
//     SparseArray<rtype::BoxColliderComponent> colliders{};
//     spriteSystem.loadTexture("BG", "./Client/assets/backgrounds/024.png");
//     spriteSystem.loadTexture("ship", "./Client/assets/ships/Spaceship.png");
//     spriteSystem.setPosition("shipSprite", 100, 100);
//
//     audioSystem.loadSound("test", "./Client/assets/sounds/Spider-Dance.wav");
//     audioSystem.playSound("test");
//     // sf::Texture text{};
//     // text.loadFromFile("./Client/assets/ships/Spaceship.png");
//
//     Entity background{manager.create_entity()};
//     Entity ship{manager.create_entity()};
//
//     sprites.emplace_at(background, spriteSystem.createSprite("BGSprite", "BG"),
//                        sf::Rect<int>{0, 0, 800, 600});
//     sprites.emplace_at(ship, spriteSystem.createSprite("shipSprite", "ship"),
//                        sf::Rect<int>{0, 0, 33, 15});
//     transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);
//     transforms.emplace_at(ship, 1.0F, 1.0F, 0.0F, 0.0F, 2.F, 2.F);
//     colliders.emplace_at(ship, 33.F, 15.F);
//     tags.emplace_at(ship, "PLAYER");
//
//     for (size_t i = 0; i < 1; i += 1) {
//         Entity ship{manager.create_entity()};
//         sprites.emplace_at(ship, spriteSystem.createSprite("shipSprite", "ship"),
//                            sf::Rect<int>{0, 0, 33, 15});
//         transforms.emplace_at(ship, 300.0F, 400.0F, 0.0F, 0.0F, 2.F, 2.F);
//         colliders.emplace_at(ship, 33.F, 15.F);
//     }
//     manager.register_component(sprites);
//     manager.register_component(tags);
//     manager.register_component(transforms);
//     manager.register_component(colliders);
//     std::function<void(ComponentManager &, float)> transform = &rtype::transform_system;
//     std::function<void(ComponentManager &, float)> movement = &rtype::movement_system;
//     std::function<void(ComponentManager &, float)> sprite = &rtype::sprite_system;
//     std::function<void(ComponentManager &, float)> collider = &rtype::collider_system;
//     manager.add_system(transform);
//     manager.add_system(movement);
//     manager.add_system(sprite);
//     float delta_time = 0.F;
//     while (le_client.is_running()) {
//         auto start = std::chrono::high_resolution_clock::now();
//         le_client.render(manager);
//         manager.apply_system(delta_time);
//         le_client.read_input();
//         auto end = std::chrono::high_resolution_clock::now();
//         delta_time =
//             std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();
//     }
//     return 0;
}

