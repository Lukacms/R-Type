/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <cstddef>
#include <rtype.hh>
#include <rtype/Client.hh>
#include <rtype/config/ArgsConfig.hh>

static int display_help()
{
    for (auto const &str : rclient::HELP_MSG) {
        std::cout << str << ENDL;
    }
    return rclient::SUCCESS;
}

int main(int argc, const char *argv[])
{
    try {
        rclient::Arguments infos{
            rclient::ArgsConfig::parse_args(argc, std::span(argv, static_cast<std::size_t>(argc)))};

        if (infos.help)
            return display_help();
        return rclient::Client::launch(infos);
    } catch (rclient::ArgsConfig::ArgsException &e) {
        std::cout << e.what() << ENDL;
        return rclient::FAILURE;
    }
}
