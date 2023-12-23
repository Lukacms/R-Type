/*
** EPITECH PROJECT, 2023
** clients
** File description:
** testsPlayer
*/

#include <gtest/gtest.h>
#include <rtype/clients/Player.hh>

TEST(Player, basic_values)
{
    rserver::Player player{asio::ip::udp::endpoint{}};

    EXPECT_EQ(player.get_port(), 0);
    EXPECT_EQ(player.get_endpoint(), asio::ip::udp::endpoint{});
    EXPECT_EQ(player.get_entity_value(), 0);
}
