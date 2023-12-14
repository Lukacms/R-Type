# Build the project

Each binary / library of the project is compiled using CMake, and we use [justfiles](https://github.com/casey/just) on Linux to facilitate the task.


Below is a overview of the different recipes, the default one being `lint`.

|       Recipe      |       Description         |
| ----------------- | ------------------------- |
|       `lint`      | Lint `.cpp`, `.hh` and `.hpp` file using clang-format.    |
|       `release`   |   Build executables that are programmed for a [release](https://en.wikipedia.org/wiki/Software_release_life_cycle)    |
|       `debug`     |   Build executables for debug. Typically with -ggdb3 flags, and other particularities.    |
|       `ninja`     |   Build release executables with [ninja](https://github.com/ninja-build/ninja) and clangd for faster compiling.   |
|       `tsan`     |   Build executables for [tsan](https://clang.llvm.org/docs/ThreadSanitizer.html). Will check for data races, ...    |
|   `tests_run`     |   Build and run tests with clangd.    |
|       `clean`     |   Clean executables.  |
|       `fclean`    |   Delete build folder and call `clean`    |
