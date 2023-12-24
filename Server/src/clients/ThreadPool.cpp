/*
** EPITECH PROJECT, 2023
** clients
** File description:
** ThreadPool
*/

#include <algorithm>
#include <mutex>
#include <rtype/clients/ThreadPool.hh>

/* constructors / destructors */
rserver::ThreadPool::ThreadPool(u_int p_nb_threads) : nb_threads{std::move(p_nb_threads)}
{
    for (u_int i = 0; i < this->nb_threads; i++) {
        this->threads.emplace_back(&ThreadPool::thread_loop, this);
    }
}

rserver::ThreadPool::~ThreadPool()
{
    this->stop();
}

rserver::ThreadPool::ThreadPool(rserver::ThreadPool &&to_move)
    : nb_threads{std::move(to_move.nb_threads)}, queue{std::move(to_move.queue)}
{
    to_move.stop();
}

/* override operator */
rserver::ThreadPool &rserver::ThreadPool::operator=(ThreadPool &&to_move)
{
    this->nb_threads = std::move(to_move.nb_threads);
    this->queue = std::move(to_move.queue);

    to_move.stop();
    return *this;
}

/* methods */
void rserver::ThreadPool::add_job(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> lock{this->mutex};
        this->queue.push(job);
    }
    this->condition.notify_one();
}

void rserver::ThreadPool::thread_loop()
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

bool rserver::ThreadPool::is_busy()
{
    bool busy{false};

    {
        std::unique_lock<std::mutex> lock{this->mutex};
        busy = !this->queue.empty();
    }
    return busy;
}

void rserver::ThreadPool::stop()
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
