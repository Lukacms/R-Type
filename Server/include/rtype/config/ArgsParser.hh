/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ArgsParser
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <exception>
#include <rtype/Manager.hh>
#include <span>
#include <string>
#include <string_view>

namespace rserver
{

    constexpr std::string_view WRONG_ARG_NB{
        "Must be either 1 or 2 arguments, try launching with -h to see the options."};
    constexpr std::string_view WRONG_TYPE{"The argument must be a positive number."};

    /* Help message */
    constexpr std::string_view HELP_INDIC{"-h"};
    constexpr std::array<std::string_view, 3> HELP_MSG{
        "USAGE ./r-type_server [port] [-h]", "\tport\tis the port number, default is 8080",
        "\t-h\tdisplay this message and exit"};

    struct Infos {
        public:
            asio::ip::port_type port{DEFAULT_PORT};
            bool help{false};
    };

    class ArgsParser
    {
        public:
            ArgsParser() = default;
            ArgsParser(ArgsParser const &to_copy) = delete;
            ArgsParser(ArgsParser &&to_move) = delete;
            ~ArgsParser() = default;
            ArgsParser &operator=(ArgsParser const &to_copy) = delete;
            ArgsParser &operator=(ArgsParser &&to_move) = delete;

            class ArgsException : public std::exception
            {
                public:
                    ArgsException(std::string p_error = DEFAULT_ERROR.data());
                    ArgsException(ArgsException const &to_copy) = default;
                    ArgsException(ArgsException &&to_move) = default;
                    ~ArgsException() override = default;
                    ArgsException &operator=(ArgsException const &to_copy) = default;
                    ArgsException &operator=(ArgsException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error_msg{};
            };

            /* methods */
            static Infos get_args(int argc, std::span<char const *> argv);

        private:
    };

} // namespace rserver
