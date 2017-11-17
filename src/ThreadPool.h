#ifndef SCOPA_THREADPOOL_H
#define SCOPA_THREADPOOL_H

#include <atomic>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include "State.h"
#include "SynchronizedQueue.h"

class ThreadPool
{
private:

    SynchronizedQueue<std::packaged_task<std::vector<int>()>> work_queue;
    void worker_thread();

    std::mutex joinMutex;
    std::condition_variable joinCV;
    std::vector<int> simulationResults; //even values = card index, odd values = simulation result for the previous card
    std::mutex resultsMutex;
public:
    explicit ThreadPool(int nr_threads = 0);
    virtual ~ThreadPool();
    void pushTask(std::packaged_task<std::vector<int>()> func);

    int getWorkQueueLength() {
        return work_queue.size();
    }

    int workingThreads = 0;
    int thread_count; //! Thread pool size
    std::atomic<bool> done; //! Thread pool status
    std::vector<std::thread> threads; //! Worker threads

    void join();
    std::vector<int> getResults();
};


#endif //SCOPA_THREADPOOL_H
