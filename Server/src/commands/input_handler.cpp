/*
** EPITECH PROJECT, 2023
** commands
** File description:
** input_handler
*/

#include <array>
#include <iostream>
#include <rtype.hh>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/Factory/ServerEntityFactory.hh>
#include <rtype/Manager.hh>
#include <vector>

static const std::array<rserver::Vector2f, 4> POSITIONS{{
    {.pos_x = 0, .pos_y = rserver::POSITION_CHANGE * -1},
    {.pos_x = rserver::POSITION_CHANGE, .pos_y = 0},
    {.pos_x = 0, .pos_y = rserver::POSITION_CHANGE},
    {.pos_x = rserver::POSITION_CHANGE * -1, .pos_y = 0},
}};

/**
 * @brief Command handler for Manager, handle the inputs sent from clients
 *
 * @param player - Player &
 * @param args - vector<string> &
 */
void rserver::Manager::input_handler(rserver::Player &player, std::vector<std::string> &args)
{
    try {
        std::unique_lock<std::shared_mutex> lock{
            this->rooms.get_room_by_id(static_cast<std::size_t>(player.get_room_id())).ecs_mutex};
        auto &room_ecs{
            this->rooms.get_room_by_id(static_cast<std::size_t>(player.get_room_id())).get_ecs()};
        auto &component{
            room_ecs.get_component<rtype::TransformComponent>(player.get_entity_value())};

        if (args.size() != 1 || !(is_number(args[0])) || args[0][0] < '0' || args[0][0] > '4') {
            throw ManagerException{WRONG_ARGUMENTS.data()};
        }
        if (args[0][0] == '4') {
            shoot_according_level(player, room_ecs, component);
            return;
        }
        component.position_x += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_x;
        component.position_y += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_y;
    } catch (game::Room::RoomException & /* e */) {
        try {
            auto &solo{this->get_solo_game(player)};
            std::unique_lock<std::shared_mutex> lock{solo.get_mutex()};
            auto &room_ecs{solo.get_ecs()};
            auto &component{
                room_ecs.get_component<rtype::TransformComponent>(player.get_entity_value())};

            if (args.size() != 1 || !(is_number(args[0])) || args[0][0] < '0' || args[0][0] > '4') {
                throw ManagerException{WRONG_ARGUMENTS.data()};
            }
            if (args[0][0] == '4') {
                shoot_according_level(player, room_ecs, component);
                return;
            }
            component.position_x += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_x;
            component.position_y += POSITIONS[static_cast<std::size_t>(args[0][0] - '0')].pos_y;
        } catch (game::solo::SoloGame::SoloException & /* e */) {
            Manager::send_message({ntw::NetworkType::Ko}, player, this->udp_socket);
        }
    }
}

/**
 * @brief Create bullet according to the level of the player
 */
void rserver::Manager::shoot_according_level(rserver::Player &player, // NOLINT
                                             rtype::ECSManager &room_ecs,
                                             rtype::TransformComponent &component)
{
    try {
        if (player.get_level() == 1) {
            size_t bullet_id{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            auto &transform_bullet{room_ecs.get_component<rtype::TransformComponent>(bullet_id)};
            transform_bullet.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet.position_y = component.position_y + OFFSET_Y_BULLET;
        } else if (player.get_level() == 2) {
            size_t bullet_id1{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            size_t bullet_id2{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            auto &transform_bullet1{room_ecs.get_component<rtype::TransformComponent>(bullet_id1)};
            auto &transform_bullet2{room_ecs.get_component<rtype::TransformComponent>(bullet_id2)};
            transform_bullet1.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet1.position_y = component.position_y + OFFSET_Y_BULLET;
            transform_bullet2.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet2.position_y = component.position_y;
        } else {
            size_t bullet_id1{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            size_t bullet_id2{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            size_t bullet_id3{ServerEntityFactory::create("PlayerBullet", room_ecs)};
            auto &transform_bullet1{room_ecs.get_component<rtype::TransformComponent>(bullet_id1)};
            auto &transform_bullet2{room_ecs.get_component<rtype::TransformComponent>(bullet_id2)};
            auto &transform_bullet3{room_ecs.get_component<rtype::TransformComponent>(bullet_id3)};
            transform_bullet1.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet1.position_y = component.position_y + OFFSET_Y_BULLET;
            transform_bullet2.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet2.position_y = component.position_y;
            transform_bullet3.position_x = component.position_x + POSITION_CHANGE;
            transform_bullet3.position_y = component.position_y;
            transform_bullet1.velocity_y = VELOCITY_BULLET;
            transform_bullet3.velocity_y = VELOCITY_BULLET * -1;
        }
    } catch (ServerEntityFactory::FactoryException &e) {
        throw ManagerException(e.what());
    }
}
