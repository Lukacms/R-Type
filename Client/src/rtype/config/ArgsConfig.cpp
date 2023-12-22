/*
** EPITECH PROJECT, 2023
** config
** File description:
** ArgsParser
*/

#include <rtype/config/ArgsConfig.hh>
#include <utility>

rclient::Arguments rclient::ArgsConfig::parse_args(int argc, std::span<const char *> argv)
{
    Arguments infos{};

    if (argc < 1 || argc > 3)
        throw ArgsException(WRONG_ARGS_NB.data());
    if (argc == 1)
        return infos;
    if (argc == 2 && std::string{argv[1]} == HELP_INDIC.data()) {
        infos.help = true;
        return infos;
    }
    infos.hostname = std::move(argv[1]);
    if (argc > 2 && std::string{argv[2]}.find_first_not_of(NUMBERS) == std::string::npos)
        infos.port = std::move(argv[2]);
    else if (argc > 2)
        throw ArgsException(PORT_IS_NB.data());
    return infos;
}

/* exception */
rclient::ArgsConfig::ArgsException::ArgsException(std::string &&perror_msg)
    : error_msg{std::move(perror_msg)}
{
}

const char *rclient::ArgsConfig::ArgsException::what() const noexcept
{
    return this->error_msg.c_str();
}
