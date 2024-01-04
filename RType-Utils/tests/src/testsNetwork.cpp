/*
** EPITECH PROJECT, 2023
** src
** File description:
** testsNetwork
*/

#include <gtest/gtest.h>
#include <rtype/network/Network.hpp>
#include <string>

TEST(Network, default_communication_values)
{
    ntw::Communication commn{};

    EXPECT_EQ(commn.type, ntw::NetworkType::None);
}

TEST(Network, add_two_int)
{
    ntw::Communication commn{};

    commn.add_param(2);
    EXPECT_EQ(std::string{commn.args.data()}, "2");
    commn.add_param(2);
    EXPECT_EQ(std::string{commn.args.data()}, "2 2");
}

TEST(Network, add_one_str_one_int)
{
    ntw::Communication commn{};

    commn.add_param("oui");
    EXPECT_EQ(std::string{commn.args.data()}, "oui");
    commn.add_param(2);
    EXPECT_EQ(std::string{commn.args.data()}, "oui 2");
}

TEST(Network, deserialize_arguments)
{
    ntw::Communication commn{.args = {"1 2 3 4"}};
    std::vector<std::string> args{"1", "2", "3", "4"};

    EXPECT_EQ(commn.deserialize(), args);
}
