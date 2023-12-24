/*
** EPITECH PROJECT, 2023
** src
** File description:
** testsDlLoader
*/

#include <dlfcn.h>
#include <gtest/gtest.h>
#include <iostream>
#include <rtype/dlloader/DlLoader.hpp>

TEST(DlLoader, errors_non_existing_lib)
{
    dl::DlLoader<std::string> loader{};

    try {
        loader.init_class<std::unique_ptr<std::string>()>("invalid path");
    } catch (dl::DlException &e) {
        dlopen("invalid path", RTLD_LAZY);
        EXPECT_EQ(std::string{e.what()}, std::string{dlerror()});
    }
}

TEST(DlLoader, errors_invalid_entrypoint)
{
    dl::DlLoader<std::string> loader{};

    try {
        loader.init_class<std::unique_ptr<std::string>()>("./libs/r-type-ecs.so",
                                                          "invalid entrypoint");
    } catch (dl::DlException &e) {
        EXPECT_EQ(std::string{e.what()}, dl::ERROR_FETCH_LOADER.data());
    }
}
