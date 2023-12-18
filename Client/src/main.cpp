/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <chrono>
#include <rtype/AudioManager.hpp>
#include <rtype/Client.hh>

int main()
{
    rclient::Client client{};
    return client.client_run();
}
