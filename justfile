# lint files with clang-format
lint:
    @clang-format -i --style='file:.clang-format' `find Server/ Client/ RType-Utils/ GameEngine/ -name *.cpp -o -name *.hh -o -name *.hpp`

names   := "r-type_server r-type_client tests-rtype-server tests-rtype-client"
name_tests_server   :=  "tests-rtype-server"
name_tests_client   :=  "tests-rtype-client"

build_folder    :=  "build"

release:
    cmake -B {{ build_folder }} -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    cmake --build {{ build_folder }} --config Release

debug:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja -C {{ build_folder }}

ninja:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=None -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja -C {{ build_folder }}

tsan:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=tsan -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true &&\
    ninja -C {{ build_folder }}

tests:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DRTYPE_BUILD_TESTS=true &&\
    ninja -C {{ build_folder }} &&\
    ./{{ name_tests_server }} && ./{{ name_tests_client }}

clean:
    @rm -rf {{ names }}

fclean: clean
    @rm -rf build
