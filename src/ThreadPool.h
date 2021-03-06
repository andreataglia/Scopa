#ifndef SCOPA_THREADPOOL_H
#define SCOPA_THREADPOOL_H

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include "SynchronizedQueue.h"
#include "mingw.thread.h"

class ThreadPool
{
private:

    SynchronizedQueue<std::function<void()>> work_queue;
    void worker_thread();

    std::mutex joinMutex;
    std::condition_variable joinCV;

public:
    explicit ThreadPool(int nr_threads = 0);
    virtual ~ThreadPool();
    void pushTask(std::function<void()> func) {
        work_queue.put(func);
        workingThreads++;
    }
    int getWorkQueueLength() {
        return work_queue.size();
    }

    int workingThreads = 0;
    int thread_count; //! Thread pool size
    std::atomic<bool> done; //! Thread pool status
    std::vector<std::thread> threads; //! Worker threads

    void join();
};


#endif //SCOPA_THREADPOOL_H
