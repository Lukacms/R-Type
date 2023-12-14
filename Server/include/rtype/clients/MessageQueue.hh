/*
** EPITECH PROJECT, 2023
** clients
** File description:
** MessageQueue
*/

#pragma once

// NOTE need to do this to be able to build the shared library of the server core
#define ASIO_HEADER_ONLY

#include <asio.hpp>
#include <rtype/network/Network.hpp>
#include <vector>

namespace rserver
{
    struct Message {
        public:
            /* variables */
            asio::ip::udp::endpoint endpoint;
            ntw::Communication communication;

            /* constructors / destructors */
            Message(asio::ip::udp::endpoint p_endpoint, ntw::Communication p_communication);
            ~Message() = default;
            Message(Message const &to_copy) = default;
            Message(Message &&to_move) = default;
            Message &operator=(Message const &to_copy) = default;
            Message &operator=(Message &&to_move) = default;
    };

    class MessageQueue
    {
        public:
            MessageQueue() = default;
            MessageQueue(MessageQueue const &to_copy) = delete;
            MessageQueue(MessageQueue &&to_move) = default;
            ~MessageQueue() = default;
            MessageQueue &operator=(MessageQueue const &to_copy) = delete;
            MessageQueue &operator=(MessageQueue &&to_move) = default;

            /* methods */
            Message pop_front();
            void push_back(Message message);
            void push_back(asio::ip::udp::endpoint endpoint, ntw::Communication communication);
            [[nodiscard]] size_t get_size_queue() const;

        private:
            std::vector<Message> messages{};
    };

} // namespace rserver
