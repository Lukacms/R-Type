/*
** EPITECH PROJECT, 2023
** commands
** File description:
** end_handler
*/

#include <rtype.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Manager.hh>

void rserver::Manager::end_handler(rserver::Player &player, std::vector<std::string> & /* args */)
{
    try {
        this->ecs.get_class().delete_entity(player.get_entity_value());
        this->players.remove_player(player);
    } catch (PlayersManager::PlayersException &e) {
        DEBUG(("%s%s", e.what(), ENDL));
    }
}
