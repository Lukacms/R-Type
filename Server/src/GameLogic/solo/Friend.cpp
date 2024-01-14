/*
** EPITECH PROJECT, 2023
** solo
** File description:
** Friend
*/

#include <algorithm>
#include <cstddef>
#include <rtype/GameLogic/solo/Friend.hh>

/* methods */
/**
 * @brief Add a move to the queue, which will be played later on
 *
 * @param move - int
 */
void rserver::game::solo::Friend::add_move_to_queue(const int &move)
{
    this->inputs.emplace(move);
}

/**
 * @brief Set a new entity id
 *
 * @param new_id - std::size_t
 */
void rserver::game::solo::Friend::set_entity_id(std::size_t new_id)
{
    this->entity_id = std::move(new_id);
}

std::size_t rserver::game::solo::Friend::get_entity_id() const
{
    return this->entity_id;
}

std::size_t rserver::game::solo::Friend::get_level() const
{
    return this->level;
}

int rserver::game::solo::Friend::pop()
{
    int popped{this->inputs.front()};

    this->inputs.pop();
    return std::move(popped);
}
