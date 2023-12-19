# R-Type
C++ Game Engine with networking

## Table of contents
1. [Project](#Project)
    1. [Dependencies](#Dependencies)
    2. [Documentation](#Documentation)
2. [Build the project](#Build)

## Project
[R-Type](https://en.wikipedia.org/wiki/R-Type) is an old arcade game.\
Our goal is to implement this game with a *multithreaded server*, a *client*, and a *game engine*.

This is a shoot'em'up, where 1 to 4 players fight against enemies, bosses and more in multiple levels.

The project is built using [CMake](https://cmake.org/), with an overlay using [justfiles](https://github.com/casey/just) to add existing rules.
You can see all the rules of the justfile [here](./docs/Build.md).

### Dependencies
The project is done in [C++](https://en.wikipedia.org/wiki/C%2B%2B), and build using [CMake](https://cmake.org/).
All other dependencies are built with cmake using FetchContent.

### Documentation
To have more information, look at the [docs](./docs/) folder.

## Build
To build the project, follow the steps below:
```bash
# Make sure you have the necessary system packages installed
# ⚠️ The following system packages installation commands may change depending on 
# your OS. Below example is for Ubuntu 20.04
sudo apt-get update -qq
sudo apt-get install -y cmake clang ninja-build just

# Have to install some libraries required for some libraries, such as SFML
sudo apt-get install -y --no-install-recommends libx11-dev libxcursor-dev libxrandr-dev libgl1-mesa-dev > /dev/null

# clone the repository
git clone git@github.com:Lukacms/R-Type.git
cd R-Type

# clone git submodules
git submodule update --init --recursive

just ninja # clangd
just release # g++
```

Once the project is built, it will have the following architecture:
```bash
.
├── build
│   └── build files
├── Client
├── CMakeLists.txt
├── GameEngine
├── justfile
├── libs
│   ├── rtype-client-core.so
│   ├── ...
│   └── rtype-server-core.so
├── README.md
├── r-type_client
├── r-type_server
├── RType-Utils
└── Server
```

## Authors
* [Luka Camus](https://github.com/Lukacms)
* [Louis Bassagal](https://github.com/LouisBassagal)
* [Samuel Florentin](https://github.com/SamuelFlorentin)
* [Elliot Janvier](https://github.com/eljanvier2)
* [Guillaume Lebreton](https://github.com/Lebonvieuxgui)
* [Melissa Laget](https://github.com/Melissa-Laget)
