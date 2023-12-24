# R-Type - Client
C++ client built with [asio](https://think-async.com/Asio/).

## Project
As the r-type is a game using network, the client is the "eyes" and the "arms" of the project. It allows the player to interact with the server via a spaceship and to see what's going on in the game.

It uses [udp](https://en.wikipedia.org/wiki/User_Datagram_Protocol) protocol to communicate with the server, and it uses the library [asio](https://think-async.com/Asio/asio-1.28.0/doc/) to handle the network.

## Thread Pool :white_check_mark:
The client is multithreaded, and uses a [thread pool](https://en.wikipedia.org/wiki/Thread_pool) to handle the commands. By default, the maximum numbers of threads are created, using the function:
```cpp
std::thread::hardware_concurrency()
```
The threads created are waiting until a command is received by the client, which will then trigger a [condition variable](https://en.cppreference.com/w/cpp/thread/condition_variable) to allow the thread to select the first command in the queue. When the command is executed, the thread will try to fetch another command, or go back into a waiting mode.\
At the end of the program, the threads are destroyed.

## Graphic :white_check_mark:

In order to display and render the dynamic elements of the game effectively, the client utilizes the [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library).

## Protocol :white_check_mark:
It manages the communication with the server. It must be a [binary protocol](https://en.wikipedia.org/wiki/Communication_protocol#Binary).\
For that, the client and server use the same `structure` that is given in the RType-Utils folder, and look like this:
```cpp
#pragma pack(push, 1)

    struct Communication {
        public:
            NetworkType type{None};
            std::array<char, MAX_SIZE> args;
    };

#pragma pack(pop)
```
The `#pragma pack` is used to avoid buffering problems.

## How to launch the project ?
```
$> ./r-type_client -h
USAGE ./r-type_client [host] [port] [-h]
        host    is the host number, default to localhost, or 0.0.0.0
        port    is the port number, default is 8080
        -h      display this message and exit
```
