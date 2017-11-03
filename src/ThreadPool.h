#ifndef SCOPA_THREADPOOL_H
#define SCOPA_THREADPOOL_H

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include "SynchronizedQueue.h"

class ThreadPool
{
private:
    std::atomic<bool> done; //! Thread pool status
    unsigned int thread_count; //! Thread pool size
    SynchronizedQueue<std::function<void()>> work_queue;
    std::vector<std::thread> threads; //! Worker threads
    void worker_thread();

public:
    ThreadPool(int nr_threads = 0);
    virtual ~ThreadPool();
    void pushTask(std::function<void ()> func) {
// SynchronizedQueue guarantees mutual exclusive access
        work_queue.put(func);
    }
    void getWorkQueueLength() {
        return work_queue.size();
    }
};


#endif //SCOPA_THREADPOOL_H