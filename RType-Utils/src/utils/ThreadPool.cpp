/*
** EPITECH PROJECT, 2023
** clients
** File description:
** ThreadPool
*/

#include <algorithm>
#include <iostream>
#include <mutex>
#include <rtype/utils/ThreadPool.hh>

/* constructors / destructors */
/**
 * @brief Constructor for ThreadPool. Construct nb_threads threads and assign them the method
 * ThreadPool::thread_loop
 *
 * @param p_nb_threads - u_int
 */
rtype::utils::ThreadPool::ThreadPool(u_int p_nb_threads) : nb_threads{std::move(p_nb_threads)}
{
    for (u_int i{0}; i < this->nb_threads; i++) {
        this->threads.emplace_back(&ThreadPool::thread_loop, this);
    }
}

rtype::utils::ThreadPool::~ThreadPool()
{
    if (this->is_busy())
        this->stop();
    std::cout << "quitting boat\n";
}

rtype::utils::ThreadPool::ThreadPool(rtype::utils::ThreadPool &&to_move)
    : nb_threads{std::move(to_move.nb_threads)}, queue{std::move(to_move.queue)}
{
    to_move.stop();
}

/* override operator */
rtype::utils::ThreadPool &rtype::utils::ThreadPool::operator=(ThreadPool &&to_move)
{
    this->nb_threads = std::move(to_move.nb_threads);
    this->queue = std::move(to_move.queue);

    to_move.stop();
    return *this;
}

/* methods */
void rtype::utils::ThreadPool::add_job(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> lock{this->mutex};
        this->queue.push(job);
    }
    this->condition.notify_one();
}

void rtype::utils::ThreadPool::thread_loop()
{
    while (!this->should_terminate) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock{this->mutex};
            this->condition.wait(lock,
                                 [this] { return this->should_terminate || !this->queue.empty(); });
            if (this->should_terminate)
                return;
            job = this->queue.front();
            this->queue.pop();
        }
        job();
    }
}

bool rtype::utils::ThreadPool::is_busy()
{
    bool busy{false};

    {
        std::unique_lock<std::mutex> lock{this->mutex};
        busy = !this->queue.empty();
    }
    return busy;
}

void rtype::utils::ThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lock{this->mutex};
        this->should_terminate = true;
    }
    this->condition.notify_all();
    for (std::thread &active : this->threads) {
        active.join();
    }
    this->threads.clear();
}