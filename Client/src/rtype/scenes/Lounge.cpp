/*
** EPITECH PROJECT, 2023
** scenes
** File description:
** Lounge
*/

#include <algorithm>
#include <iostream>
#include <rtype/Client.hh>
#include <rtype/scenes/Lounge.hh>
#include <rtype/utils/Vector2D.hpp>

static const std::vector<rclient::scenes::LoungeNtwHandler> LOUNGE_HANDLER{
    {ntw::NetworkType::Room, &rclient::scenes::Lounge::rooms_handler},
    {ntw::NetworkType::End, &rclient::scenes::Lounge::end_handler},
    {ntw::NetworkType::ToGame, &rclient::scenes::Lounge::to_game_handler},
};

/* ctor / dtor */
rclient::scenes::Lounge::Lounge(asio::ip::udp::socket &psocket, asio::ip::udp::endpoint &pendpoint,
                                const unsigned int &pwidth, const unsigned int &pheight)
    : width{pwidth}, height{pheight}, endpoint{pendpoint}, socket{psocket}
{
    this->scrollable.setViewport(VIEWPORT);
    this->transforms[0].scale_x = static_cast<float>(pwidth) / MENU_BG_WIDTH;
    this->transforms[0].scale_y = static_cast<float>(pheight) / MENU_BG_HEIGHT;
    this->transforms[1].scale_x = 3;
    this->transforms[1].scale_y = 3;
    this->font.loadFromFile(FONT_FILE.data());
    this->text.setFont(this->font);
    this->text.setString(NEW_ROOM.data());
    this->text.setCharacterSize(PLAY_FONT_SIZE);
    this->text.setFillColor(sf::Color::Black);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, 0);
}

/* methods */
void rclient::scenes::Lounge::display(rtype::IGraphicModule &graphics)
{
    sf::View basic{graphics.get_view_port()};
    rtype::utils::Vector2D<float> local{0, 90};
    rtype::TransformComponent boxes{this->transforms[this->transforms.size() - 1]};

    graphics.clear();
    for (unsigned int i{0}; i < this->paths.size(); i++) {
        this->texture.loadFromFile(this->paths[i]);
        this->sprite.setTexture(this->texture);
        graphics.draw(this->sprite, this->transforms[i]);
    }
    this->texture.loadFromFile(ROOM_CONTAINER.data());
    this->sprite.setTexture(this->texture);
    graphics.set_view_port(this->scrollable);
    this->sprite.setOrigin(components::ORIGIN_BOX);
    boxes.position_y = this->global_pos.y;
    for (auto &room : this->rooms) {
        boxes.position_y += local.y;
        room.display(graphics, this->sprite, boxes);
        local.y = 200;
        local.x = boxes.position_y + this->sprite.getGlobalBounds().height + local.y;
    }
    this->end = local.x;
    graphics.set_view_port(basic);
    this->sprite.setOrigin({0, 0});
    this->text.setString(NEW_ROOM.data());
    this->text.setCharacterSize(PLAY_FONT_SIZE);
    rtype::TransformComponent tmp{};
    tmp.position_x = this->width / MIDLE_DIV - TEXT_POS_LOUNGE * 2;
    tmp.position_y = this->height - TEXT_POS_LOUNGE;
    graphics.draw(this->text, tmp);
    this->new_box = this->text.getGlobalBounds();
    this->text.setString(JOIN_ROOM.data());
    graphics.draw(this->text, tmp);
    this->join_box = this->text.getGlobalBounds();
    this->transforms.back().position_y = TEXT_POS_LOUNGE;
    graphics.display();
    this->rooms.clear();
}

void rclient::scenes::Lounge::handle_events(rtype::IGraphicModule &graphics,
                                            rtype::IAudioModule & /*audio*/, State & /* state */)
{
    rtype::utils::Vector2D<float> mouse{graphics.is_left_mouse_pressed()};

    if (mouse.x > -1 && mouse.y > -1 && new_room.get_elapsed_time_in_ms() > ROOM_TIMEOUT) {
        if (this->new_box.contains(mouse.x, mouse.y)) {
            Client::send_message({ntw::NetworkType::Room}, this->endpoint, this->socket);
        }
        if (this->join_box.contains(mouse.x, mouse.y)) {
            ntw::Communication commn{ntw::NetworkType::Room};
            commn.add_param(-1);
            Client::send_message(commn, this->endpoint, this->socket);
        }
        this->new_room.reset();
    }
    if (graphics.is_input_pressed(rtype::Keys::UP) &&
        this->end + this->global_pos.y > this->scrollable.getSize().y) {
        this->global_pos.y -= CHANGE_SCROLL;
    }
    if (graphics.is_input_pressed(rtype::Keys::DOWN) && this->global_pos.y < 0) {
        this->global_pos.y += CHANGE_SCROLL;
    }
}

/* network functions */
void rclient::scenes::Lounge::handle_network(ntw::Communication &commn,
                                             rtype::IAudioModule & /*audio*/, State &state)

{
    std::vector<std::string> arguments{commn.deserialize()};

    for (const auto &handler : LOUNGE_HANDLER) {
        if (commn.type == handler.type)
            return handler.handler(*this, arguments, state);
    }
}

void rclient::scenes::Lounge::rooms_handler(std::vector<std::string> &args, State & /* state */)
{
    if (args.size() != 3)
        return;
    unsigned int r_id{static_cast<unsigned int>(std::stoi(args[0]))};
    unsigned int players{static_cast<unsigned int>(std::stoi(args[1]))};
    unsigned short status{static_cast<unsigned short>(std::stoi(args[1]))};

    for (auto &room : this->rooms) {
        if (room.get_id() == r_id) {
            room.set_status(status);
            room.set_nb_players(players);
            return;
        }
    }
    auto &created{this->rooms.emplace_back(r_id, this->font)};
    created.set_status(status);
    created.set_nb_players(players);
}

void rclient::scenes::Lounge::end_handler(std::vector<std::string> & /* args */, // NOLINT
                                          State &state)
{
    state = State::End;
}

void rclient::scenes::Lounge::to_game_handler(std::vector<std::string> & /* args */, // NOLINT
                                              State &state)
{
    state = State::Game;
}
