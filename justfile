# lint files with clang-format
lint:
    @find -name *.cpp -o -name *.hpp -o -name *.hh | xargs clang-format -i

names := "r-type_server r-type_client tests-rtype-server tests-rtype-client"
name_tests_server  :=  "tests-rtype-server"
name_tests_client  :=  "tests-rtype-client"

make_build:
    @mkdir -p build

release: make_build
    cd build &&\
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    cmake --build .

debug: make_build
    cd build &&\
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true\
    cmake --build .

ninja: make_build
    cd build &&\
    cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja

tests: make_build
    cd build &&\
    cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DRAYTRACER_BUILD_TESTS=true &&\
    ninja &&\
    cd .. && ./{{ name_tests_server }} && ./{{ name_tests_client }}

clean:
    @rm -rf {{ names }}

fclean: clean
    @rm -rf build
