# lint files with clang-format
lint:
    @clang-format -i --style='file:.clang-format' `find Server/ Client/ RType-Utils/ GameEngine/ -name *.cpp -o -name *.hh -o -name *.hpp`

names := "r-type_server r-type_client tests-rtype-server tests-rtype-client"
name_tests_server  :=  "tests-rtype-server"
name_tests_client  :=  "tests-rtype-client"

release:
    cmake -B build/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    cmake --build build --config Release

debug:
    cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja -C build

ninja:
    cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja -C build

tests:
    cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DRTYPE_BUILD_TESTS=true &&\
    ninja -C build &&\
    ./{{ name_tests_server }} && ./{{ name_tests_client }}

clean:
    @rm -rf {{ names }}

fclean: clean
    @rm -rf build
