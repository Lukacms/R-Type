/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <rtype.hh>
#include <rtype/Manager.hh>

int main(int /* argc */, const char * /* argv */[])
{
    rserver::Manager::launch(rserver::DEFAULT_PORT);

    return rserver::SUCESS;
}
