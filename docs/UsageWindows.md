# Usage Windows

How to build the binaries / libs on windows.

Make sure to have the following package installed. Name may vary:
* just
* cmake
* clang
* ninja-build
* dlfcn-win32 with `vcpkg`

And for SFML:
* libxrandr-dev
* libxcursor-dev
* libudev-dev
* libopenal-dev
* libflac-dev
* libvorbis-dev
* libgl1-mesa-dev
* libegl1-mesa-dev
* libdrm-dev
* libgbm-dev

You can then launch the project with `just windows`.

Or the command:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release ; cmake --build build
```
The executables will be in Debug subdirectory:
```
.
├── build
│   └── build files
├── Client
├── CMakeLists.txt
├── GameEngine
├── justfile
├── libs
│   ├── Debug
│   │   ├── rtype-client-core.dll
│   │   ├── ...
│   │   └── rtype-server-core.dll
├── README.md
├── Debug
│   ├── r-type_client
│   └── r-type_server
├── RType-Utils
└── Server
```
Then, unzip the `assets.zip` file, move `r-type_server` and `r-type_client` binaries from the Debug subdirectory to the root directory. Also move the dll files in `libs/Debug` to the root. You can then launch the binaries !
