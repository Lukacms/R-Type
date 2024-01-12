/*
** EPITECH PROJECT, 2024
** config
** File description:
** ConfigsFile
*/

#pragma once

#include <exception>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <vector>

using njson = nlohmann::json;

namespace rserver::config
{
    constexpr std::string_view ERROR_LEVEL{"R-Type : Unable to load the following level : "};
    constexpr std::string_view LEVEL_FOLDER{"./assets/configs/level/"};
    constexpr std::string_view MUSIC_FOLDER{"./assets/BGM"};
    constexpr std::string_view MUSIC_EXT{".ogg"};

    struct Wave {
        public:
            double time;
            bool is_done{false};
            std::vector<std::string> enemies;
    };

    struct Level {
        public:
            std::string title;
            std::string background;
            std::string music;
            double time;
            std::vector<Wave> waves;
    };

    class ConfigsFile
    {
        public:
            ConfigsFile() = default;
            ConfigsFile(ConfigsFile const &to_copy) = default;
            ConfigsFile(ConfigsFile &&to_move) = default;
            ~ConfigsFile() = default;
            ConfigsFile &operator=(ConfigsFile const &to_copy) = default;
            ConfigsFile &operator=(ConfigsFile &&to_move) = default;

            /* static method to parse all levels. */
            static std::vector<Level> parse();

            std::vector<Level> do_parse();
            void add_enemies(const njson &enemies);

            class ConfigsException : public std::exception
            {
                public:
                    ConfigsException(std::string perror = "Error");
                    ConfigsException(ConfigsException const &to_copy) = default;
                    ConfigsException(ConfigsException &&to_move) = default;
                    ~ConfigsException() override = default;
                    ConfigsException &operator=(ConfigsException const &to_copy) = default;
                    ConfigsException &operator=(ConfigsException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error{"Error"};
            };

        private:
            njson json;
            njson entities{};
            std::vector<Level> levels{};
    };

} // namespace rserver::config
