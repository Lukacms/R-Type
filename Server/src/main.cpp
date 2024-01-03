/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <iostream>
#include <rtype.hh>
#include <rtype/Manager.hh>
#include <rtype/config/ArgsParser.hh>

/**
 * @brief Show help message
 *
 * @return SUCCESS
 */
static int display_help()
{
    for (auto const &str : rserver::HELP_MSG) {
        std::cout << str << ENDL;
    }
    return rserver::SUCCESS;
}

/**
 * @brief Main function. Load the arguments and launch the server's manager.
 *
 * @param argc int - nb of args
 * @param argv const char[] - array with the arguments
 * @return int - SUCCESS (0) is okay, else FAILURE (84)
 */
int main(int argc, const char *argv[])
{
    std::srand(std::time(nullptr));
    try {
        rserver::Infos infos{
            rserver::ArgsParser::get_args(argc, std::span(argv, std::size_t(argc)))};

        if (infos.help)
            return display_help();
        rserver::Manager::launch(rserver::DEFAULT_PORT);
    } catch (rserver::ArgsParser::ArgsException &e) {
        std::cout << e.what() << ENDL;
        return rserver::FAILURE;
    }

    return rserver::SUCCESS;
}
