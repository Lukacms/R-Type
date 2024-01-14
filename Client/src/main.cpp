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

/**
 * @brief Display help message
 *
 * @return int - SUCCESS (0)
 */
static int display_help()
{
    for (auto const &str : rclient::HELP_MSG) {
        std::cout << str << ENDL;
    }
    return rclient::SUCCESS;
}

/**
 * @brief Main function, to launch all parts
 *
 * @param argc - int
 * @param argv - const char *[]
 * @return - int - SUCCESS (0) | FAILURE (84)
 */
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
