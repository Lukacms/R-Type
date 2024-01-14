/*
** EPITECH PROJECT, 2023
** clients
** File description:
** testsThreadPool
*/

#include <gtest/gtest.h>
#include <rtype/utils/ThreadPool.hh>
#include <unistd.h>

TEST(ThreadPool, constructing_pool_one_thread)
{
    rtype::utils::ThreadPool pool{1};

    EXPECT_FALSE(pool.is_busy());
    pool.add_job([]() { sleep(10); }); // NOLINT
    EXPECT_TRUE(pool.is_busy());
    pool.stop();
}
