# lint files with clang-format
lint:
    @clang-format -i --style='file:.clang-format' `find Server/ Client/ RType-Utils/ GameEngine/ -name *.cpp -o -name *.hh -o -name *.hpp`

names   := "r-type_server r-type_client"
name_tests_server   :=  "tests/tests-r-type_server"
name_tests_client   :=  "tests/tests-r-type_client"

build_folder    :=  "build"

basic_options   := '-DCMAKE_EXPORT_COMPILE_COMMANDS=true -DCMAKE_CXX_COMPILER_LAUNCHER=ccache'
no_release  :=  '-DUSE_CLANG_TIDY=false -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ '

release:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ {{ basic_options }} &&\
    ninja -C {{ build_folder }} && cd {{ build_folder }} && sudo cpack --config CPackConfig.cmake

debug:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Debug {{ no_release }} {{ basic_options }} &&\
    ninja -C {{ build_folder }}

ninja:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=None {{ no_release }} {{ basic_options }} &&\
    ninja -C {{ build_folder }}

tsan:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=tsan {{ no_release }} {{ basic_options }} &&\
    ninja -C {{ build_folder }}

clean_tests:
    @find -name *.gc* -delete

tests: clean_tests
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ {{ basic_options }} -DRTYPE_BUILD_TESTS=true &&\
    ninja -C {{ build_folder }}

# compile on windows
windows:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Release {{ basic_options }} -DASIO_STANDALONE=true --preset debug &&\
    ninja -C {{ build_folder }}

benchmarks:
    cmake -B {{ build_folder }} -GNinja -DCMAKE_BUILD_TYPE=Release {{ no_release }} {{ basic_options }} -DRTYPE_BUILD_BENCHMARKS=true &&\
    ninja -C {{ build_folder }}

clean:
    @rm -rf {{ names }}

fclean: clean
    @rm -rf build tests libs
