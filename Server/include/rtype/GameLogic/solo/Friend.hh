/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Friend
*/

#include <queue>

namespace rserver::game::solo
{

    class Friend
    {
        public:
            Friend() = default;
            Friend(Friend const &to_copy) = default;
            Friend(Friend &&to_move) = default;
            ~Friend() = default;
            Friend &operator=(Friend const &to_copy) = default;
            Friend &operator=(Friend &&to_move) = default;

            /* methods */
            void add_move_to_queue(const int &move);

        private:
            std::queue<int> inputs{};
            std::size_t level{1};
    };

} // namespace rserver::game::solo
