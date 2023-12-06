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
#include <rtype/Client.hpp>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TagComponent.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/ECSManager.hpp>
#include <chrono>

int main(int /* argc */, const char * /* argv */[])
{
    rclient::Client le_client{};
    rtype::ECSManager manager{};
    SparseArray<SpriteComponent> sprites{};
    SparseArray<TransformComponent> transforms{};
    SparseArray<TagComponent> tags{};
    sf::Texture text{};
    text.loadFromFile("./Client/assets/Spaceship.png");

    Entity ship{manager.create_entity()};

    sprites.emplace_at(ship, sf::Sprite{text}, sf::Rect<int>{0, 0, 33, 15});
    transforms.emplace_at(ship, 1.0F, 1.0F, 0.0F, 0.0F, 2.F, 2.F);
    tags.emplace_at(ship, "PLAYER");

    for (size_t i = 0; i < 9999; i += 1) {
        Entity ship{manager.create_entity()};

        sprites.emplace_at(ship, sf::Sprite{text}, sf::Rect<int>{0, 0, 33, 15});
        transforms.emplace_at(ship, 1.0F, 1.0F, 0.0F, 0.0F, 2.F, 2.F);
    }
    manager.register_component(sprites);
    manager.register_component(tags);
    manager.register_component(transforms);
    std::function<void(Registry &, float)> transform = &rtype::transform_system;
    std::function<void(Registry &, float)> movement = &rtype::movement_system;
    std::function<void(Registry &, float)> sprite = &rtype::sprite_system;
    manager.add_system(transform);
    manager.add_system(movement);
    manager.add_system(sprite);
    float delta_time = 0.F;
    while (le_client.is_running()) {
        auto start = std::chrono::high_resolution_clock::now();
        le_client.render(manager);
        manager.apply_system(delta_time * 144);
        le_client.read_input();
        auto end = std::chrono::high_resolution_clock::now();
        delta_time = std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();
    }
    return 0;
}
