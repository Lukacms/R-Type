/*
** EPITECH PROJECT, 2023
** clients
** File description:
** MessageQueue
*/

#include <algorithm>
#include <rtype/clients/MessageQueue.hh>

/* struct message */
rserver::Message::Message(asio::ip::port_type p_port, ntw::Communication p_communication)
    : port{std::move(p_port)}, communication{std::move(p_communication)}
{
}

/* class MessageQueue */
rserver::Message rserver::MessageQueue::pop_front()
{
    auto dest{this->messages.front()};

    this->messages.erase(this->messages.begin(), this->messages.begin() + 1);
    return dest;
}

void rserver::MessageQueue::push_back(rserver::Message message)
{
    this->messages.emplace_back(std::move(message));
}

void rserver::MessageQueue::push_back(asio::ip::port_type port, ntw::Communication communication)
{
    this->messages.emplace_back(std::move(port), std::move(communication));
}

size_t rserver::MessageQueue::get_size_queue() const
{
    return this->messages.size();
}
