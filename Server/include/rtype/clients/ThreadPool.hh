/*
** EPITECH PROJECT, 2023
** clients
** File description:
** ThreadPool
*/

#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using u_int = unsigned int;

namespace rserver
{

    class ThreadPool
    {
        public:
            /* constructors / destructors */
            /**
             * @brief construct a new ThreadPool object. Sould be only one in project, no need for
             * more
             *
             * @param p_nb_threads - u_int - default is max threads that the system supports
             */
            ThreadPool(u_int p_nb_threads = std::thread::hardware_concurrency());
            ThreadPool(ThreadPool const &to_copy) = delete;
            ThreadPool(ThreadPool &&to_move);
            ~ThreadPool() = default;

            /* override operator */
            ThreadPool &operator=(ThreadPool const &to_copy) = delete;
            ThreadPool &operator=(ThreadPool &&to_move);

            /* methods */
            void add_job(const std::function<void()> &job);
            void stop();
            [[nodiscard]] bool is_busy();

        private:
            /* variables */
            u_int nb_threads;
            mutable std::mutex mutex{};
            std::condition_variable condition{};
            std::vector<std::thread> threads{};
            std::queue<std::function<void()>> queue{};

            bool should_terminate{false};

            /* methods */
            void thread_loop();
    };

} // namespace rserver
