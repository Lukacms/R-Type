/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/
/*
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
*/
#include <rtype/Client.hpp>
#include <rtype/Components/SpriteComponent.hpp>
#include <rtype/Components/TagComponent.hpp>
#include <rtype/Components/TransformComponent.hpp>
#include <rtype/Systems/AudioSystem.hpp>

int main(int /* argc */, const char * /* argv */[])
{
    rclient::Client client{};
    Entity ship{2};
    Entity test{5};
    Entity background{1};

    SparseArray<SpriteComponent> sprites{};
    SparseArray<TransformComponent> transforms{};
    SparseArray<TagComponent> tags{};
    sf::Texture text{};
    AudioManager audioSystem{};
    sf::Texture bg{};
    bg.loadFromFile("./Client/assets/backgrounds/024.png");
    sprites.emplace_at(background, sf::Sprite{bg}, sf::Rect<int>{0, 0, 800, 600});
    transforms.emplace_at(background, 0.0F, 0.0F, 0.0F, 0.0F, 1.F, 1.F);
    tags.emplace_at(background, "BACKGROUND");

    text.loadFromFile("./Client/assets/ships/Spaceship.png");
    audioSystem.loadSound("test", "./Client/assets/sounds/Spider-Dance.wav");
    audioSystem.playSound("test");

    sprites.emplace_at(ship, sf::Sprite{text}, sf::Rect<int>{0, 0, 33, 15});
    transforms.emplace_at(ship, 1.0F, 1.0F, 0.0F, 0.0F, 2.F, 2.F);
    tags.emplace_at(ship, "PLAYER");
    sprites.emplace_at(test, sf::Sprite{text}, sf::Rect<int>{33, 0, 33, 15});
    transforms.emplace_at(test, 300.0F, 400.0F, 0.0F, 0.0F, 2.F, 2.F);
    tags.emplace_at(test, "ENEMY");
    client.get_registry().register_component(sprites);
    client.get_registry().register_component(transforms);
    client.get_registry().register_component(tags);
    while (client.is_running()) {
        client.read_input();
        client.render();
        client.update();
    }
    return 0;
}
