/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Solo
*/

#pragma once

#include <exception>
#include <rtype/GameLogic/GameLogic.hh>
#include <rtype/GameLogic/solo/Friend.hh>
#include <rtype/PhysicsManager.hh>
#include <rtype/clients/Player.hh>
#include <rtype/dlloader/DlLoader.hpp>
#include <rtype/utils/Clock.hh>
#include <shared_mutex>
#include <string_view>

namespace rserver::game::solo
{

    constexpr std::string_view END{"End of Game."};
    constexpr std::string_view DEL_ENTITY{"Del entity"};

    class SoloGame
    {
        public:
            /* threads */
            std::shared_mutex mutex{};

            SoloGame(asio::ip::udp::socket &psocket, Player &pplayer);
            SoloGame(SoloGame const &to_copy) = delete;
            SoloGame(SoloGame &&to_move);
            ~SoloGame() = default;
            SoloGame &operator=(SoloGame const &to_copy) = delete;
            SoloGame &operator=(SoloGame &&to_move);

            void game_turn(rtype::utils::Clock &clock);
            [[nodiscard]] Player &get_player() const;
            void add_move_to_friend(const int &move);
            [[nodiscard]] Friend &get_friend_by_id(const std::size_t &entity_id);
            void delete_friend(const std::size_t &entity_id);
            [[noreturn]] void end_game();
            [[nodiscard("Pls get the variable")]] rtype::ECSManager &get_ecs() const;
            [[nodiscard("Pls get the variable")]] std::shared_mutex &get_mutex();

            class SoloException : std::exception
            {
                public:
                    SoloException(const std::string &perror = "Error");
                    SoloException(SoloException const &to_copy) = default;
                    SoloException(SoloException &&to_move) = default;
                    ~SoloException() override = default;
                    SoloException &operator=(SoloException const &to_copy) = default;
                    SoloException &operator=(SoloException &&to_move) = default;

                    [[nodiscard]] const char *what() const noexcept override;

                private:
                    std::string error;
            };

        private:
            GameLogic game;
            Player &player;
            dl::DlLoader<rtype::ECSManager> ecs{};
            dl::DlLoader<rtype::PhysicsManager> physics{};
            std::vector<Friend> ai{};

            asio::ip::udp::socket &socket;
            std::shared_mutex ecs_mutex;
    };

} // namespace rserver::game::solo
