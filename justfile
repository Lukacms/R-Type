# lint files with clang-format
lint:
    @find -name *.cpp -o -name *.hpp -o -name *.hh | xargs clang-format -i

make_build:
    @mkdir -p build && cd build

release: make_build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true
    cmake --build .

debug: make_build
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true
    cmake --build .

ninja: make_build
    cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true
    ninja

tests: make_build
    cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DRAYTRACER_BUILD_TESTS=true
    ninja
    cd .. && ./tests-raytracer

