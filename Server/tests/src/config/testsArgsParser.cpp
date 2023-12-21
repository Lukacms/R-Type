/*
** EPITECH PROJECT, 2023
** config
** File description:
** testsArgsParser
*/

#include <gtest/gtest.h>
#include <rtype/config/ArgsParser.hh>
#include <span>

TEST(ArgsParser, get_args_help)
{
    const char *argv[]{"kfj", "-h"}; // NOLINT
    rserver::Infos parsed{rserver::ArgsParser::get_args(2, std::span(argv, 2))};

    EXPECT_TRUE(parsed.help);
}

TEST(ArgsParser, get_args_wrong_arg_nb)
{
    const char *argv_too_little[]{};                     // NOLINT
    const char *argv_too_much[]{"lkjeza", "ljh", "lkh"}; // NOLINT

    EXPECT_THROW(rserver::ArgsParser::get_args(0, std::span(argv_too_little, 0)),
                 rserver::ArgsParser::ArgsException);
    EXPECT_THROW(rserver::ArgsParser::get_args(3, std::span(argv_too_much, 3)),
                 rserver::ArgsParser::ArgsException);
}

TEST(ArgsParser, get_port)
{
    const char *none[]{"lkhg"};         // NOLINT
    const char *some[]{"kelj", "8909"}; // NOLINT
    rserver::Infos none_infos{rserver::ArgsParser::get_args(1, std::span(none, 1))};
    rserver::Infos some_infos{rserver::ArgsParser::get_args(2, std::span(some, 2))};

    EXPECT_EQ(none_infos.port, 8080);
    EXPECT_EQ(some_infos.port, 8909);
}
