/*
** EPITECH PROJECT, 2023
** clients
** File description:
** testsPlayer
*/

#include <gtest/gtest.h>
#include <rtype/clients/Player.hh>
#include <rtype/clients/PlayersManager.hh>

TEST(Player, basic_values)
{
    rserver::Player player{asio::ip::udp::endpoint{}};

    EXPECT_EQ(player.get_port(), 0);
    EXPECT_EQ(player.get_endpoint(), asio::ip::udp::endpoint{});
    EXPECT_EQ(player.get_entity_value(), 0);
}

TEST(PlayersManager, add_new_player)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    EXPECT_EQ(manager.length(), 0);
    EXPECT_NO_THROW(manager.add_player(endpoint));
    EXPECT_EQ(manager.length(), 1);
}

TEST(PlayersManager, add_new_player_and_get_all)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    EXPECT_EQ(manager.length(), 0);
    auto &player{manager.add_player(endpoint)};
    EXPECT_EQ(manager.length(), 1);
    const auto &players{manager.get_all_players()};
    EXPECT_EQ(player.get_endpoint(), players.front().get_endpoint());
}

TEST(PlayersManager, getting_player_by_id_success)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    auto &player{manager.add_player(endpoint)};
    EXPECT_NO_THROW(manager.get_by_id(player.get_port())); // NOLINT
}

TEST(PlayersManager, getting_player_by_id_failure)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    manager.add_player(endpoint);
    EXPECT_THROW(manager.get_by_id(35487), rserver::PlayersManager::PlayersException); // NOLINT
}

TEST(PlayersManager, getting_player_by_entity_success)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    auto &player{manager.add_player(endpoint)};
    EXPECT_NO_THROW(manager.get_by_entity_id(player.get_entity_value())); // NOLINT
}

TEST(PlayersManager, getting_player_by_entity_failure)
{
    rserver::PlayersManager manager{};
    asio::ip::udp::endpoint endpoint{};

    manager.add_player(endpoint);
    EXPECT_THROW(manager.get_by_entity_id(35487), // NOLINT
                 rserver::PlayersManager::PlayersException);
}
