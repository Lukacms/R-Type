/*
** EPITECH PROJECT, 2023
** src
** File description:
** utils
*/

#include <gtest/gtest.h>
#include <rtype.hh>
#include <vector>

TEST(Utils, is_number_true_values)
{
    EXPECT_TRUE(rserver::is_number("12"));
    EXPECT_TRUE(rserver::is_number("76"));
    EXPECT_TRUE(rserver::is_number("76652467"));
}

TEST(Utils, is_number_false_values)
{
    EXPECT_FALSE(rserver::is_number("12a"));
    EXPECT_FALSE(rserver::is_number("kel"));
    EXPECT_FALSE(rserver::is_number("-76652467"));
}

TEST(Utils, get_number_basic)
{
    EXPECT_EQ(rserver::get_number("8"), 8);
    EXPECT_EQ(rserver::get_number("17"), 17);
}

TEST(Utils, get_number_partial)
{
    EXPECT_EQ(rserver::get_number("8a"), 8);
    EXPECT_EQ(rserver::get_number("17ngh8"), 17);
}

TEST(Utils, get_number_errors)
{
    EXPECT_EQ(rserver::get_number("a"), 0);
    EXPECT_EQ(rserver::get_number("gh8"), 0);
}

TEST(Utils, split_delimitor_basic)
{
    std::vector<std::string> res{"a", "b"};

    EXPECT_EQ(rserver::split_delimitor("a b", " "), res);
}

TEST(Utils, split_delimitor_empty_string)
{
    std::vector<std::string> res{};

    EXPECT_EQ(rserver::split_delimitor("", " "), res);
}

TEST(Utils, split_delimitor_empty_del)
{
    std::vector<std::string> res{"a b"};

    EXPECT_EQ(rserver::split_delimitor("a b", ""), res);
}
