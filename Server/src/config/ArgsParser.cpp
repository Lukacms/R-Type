/*
** EPITECH PROJECT, 2023
** config
** File description:
** ArgsParser
*/

#include <algorithm>
#include <rtype.hh>
#include <rtype/config/ArgsParser.hh>

/* methods */
/**
 * @brief Static method to parse args given in agruments
 *
 * @param argc - int
 * @param argv - span<const char *>
 * @return Infos
 * @throws ArgsException on error
 */
rserver::Infos rserver::ArgsParser::get_args(int argc, std::span<const char *> argv)
{
    Infos infos{};

    if (argc < 1 || argc > 2)
        throw ArgsException(WRONG_ARG_NB.data());
    if (argc == 1)
        return infos;
    if (std::string{argv[1]} == HELP_INDIC.data()) {
        infos.help = true;
        return infos;
    }
    if (!is_number(std::string{argv[1]}))
        throw ArgsException();
    infos.port = static_cast<asio::ip::port_type>(get_number<std::size_t>(argv[1]));
    return infos;
}

/* exception */
rserver::ArgsParser::ArgsException::ArgsException(std::string p_error)
    : error_msg{std::move(p_error)}
{
}

const char *rserver::ArgsParser::ArgsException::what() const noexcept
{
    return this->error_msg.data();
}
