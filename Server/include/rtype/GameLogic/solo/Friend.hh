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
            void set_entity_id(std::size_t new_id);
            [[nodiscard]] std::size_t get_entity_id() const;
            [[nodiscard]] std::size_t get_level() const;
            [[nodiscard]] int pop();

        private:
            std::queue<int> inputs{};
            std::size_t level{1};
            std::size_t entity_id{0};
    };

} // namespace rserver::game::solo
