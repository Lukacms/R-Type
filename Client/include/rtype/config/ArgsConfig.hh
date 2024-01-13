/*
** EPITECH PROJECT, 2023
** config
** File description:
** ArgsConfig
*/

#pragma once

#include <exception>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace rclient
{
    constexpr std::string_view DEFAULT_HOST{"0.0.0.0"};
    constexpr std::string_view DEFAULT_PORT{"8080"};
    constexpr std::string_view HELP_INDIC{"-h"};
    static const std::vector<std::string> HELP_MSG{
        "USAGE ./r-type_client [host] [port] [-h]",
        "\thost\tis the host number, default to localhost, or 0.0.0.0",
        "\tport\tis the port number, default is 8080", "\t-h\tdisplay this message and exit"};
    constexpr std::string_view NUMBERS{"0123456789"};

    constexpr std::string_view WRONG_ARGS_NB{"Wrong number of arguments."};
    constexpr std::string_view PORT_IS_NB{"The port argument should be a positive number."};

    struct Arguments {
        public:
            std::string port{DEFAULT_PORT.data()};
            std::string hostname{DEFAULT_HOST.data()};
            bool help{false};
    };

    class ArgsConfig
    {
        public:
            /* ctor / dtor */
            ArgsConfig() = default;
            ArgsConfig(ArgsConfig const &to_copy) = default;
            ArgsConfig(ArgsConfig &&to_move) = default;
            ~ArgsConfig() = default;

            /* operator override */
            ArgsConfig &operator=(ArgsConfig const &to_copy) = default;
            ArgsConfig &operator=(ArgsConfig &&to_move) = default;

            /* methods */
            static Arguments parse_args(int argc, std::span<const char *> argv);

            class ArgsException : std::exception
            {
                public:
                    ArgsException(std::string &&perror_msg);
                    ArgsException(ArgsException const &to_copy) = default;
                    ArgsException(ArgsException &&to_move) = default;
                    ~ArgsException() override = default;
                    ArgsException &operator=(ArgsException const &to_copy) = default;
                    ArgsException &operator=(ArgsException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{"Error"};
            };

        private:
    };

} // namespace rclient
