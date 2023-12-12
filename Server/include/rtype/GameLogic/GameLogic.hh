//
// Created by kane on 12/12/23.
//

#pragma once

#include <rtype/ECSManager.hpp>

class GameLogic {
    public:
        GameLogic() = default;
        GameLogic(GameLogic const &to_copy) = default;
        GameLogic(GameLogic &&to_move);
        ~GameLogic();
        GameLogic &operator=(GameLogic const &to_copy) = delete;
        GameLogic &operator=(GameLogic &&to_move);

        void game_loop(rtype::ECSManager &manager);

    private:
        std::vector<std::size_t> m_players;
        std::vector<std::size_t> m_enemies;

};
