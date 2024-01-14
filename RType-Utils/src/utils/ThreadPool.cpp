/*
** EPITECH PROJECT, 2023
** clients
** File description:
** ThreadPool
*/

#include <algorithm>
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

/**
 * @brief Destructor for thread pool. Stops threads
 */
rtype::utils::ThreadPool::~ThreadPool()
{
    if (this->is_busy())
        this->stop();
}

/**
 * @brief Constructor by move
 *
 * @param to_move - ThreadPool &&
 */
rtype::utils::ThreadPool::ThreadPool(rtype::utils::ThreadPool &&to_move)
    : nb_threads{std::move(to_move.nb_threads)}, queue{std::move(to_move.queue)}
{
    to_move.stop();
}

/* override operator */
/**
 * @brief Operator equal by move
 *
 * @param to_move - ThreadPool &&
 * @return - ThreadPool & - this
 */
rtype::utils::ThreadPool &rtype::utils::ThreadPool::operator=(ThreadPool &&to_move)
{
    this->nb_threads = std::move(to_move.nb_threads);
    this->queue = std::move(to_move.queue);

    to_move.stop();
    return *this;
}

/* methods */
/**
 * @brief Add a job to do to the queue of jobs. The job must be a function returning void and taking
 * no param (can and should be a lambda)
 *
 * @param job - std::function<void()> &
 */
void rtype::utils::ThreadPool::add_job(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> lock{this->mutex};
        this->queue.push(job);
    }
    this->condition.notify_one();
}

/**
 * @brief Function that is called for every thread. Run as long as the variable `should_terminate`
 * is set to true
 */
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

/**
 * @brief Return if the pool is busy, which means if there are jobs in the queue
 *
 * @return bool
 */
bool rtype::utils::ThreadPool::is_busy()
{
    bool busy{false};

    {
        std::unique_lock<std::mutex> lock{this->mutex};
        busy = !this->queue.empty();
    }
    return busy;
}

/**
 * @brief Stops every thread of the pool
 */
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
