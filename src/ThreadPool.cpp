//
// Created by Spranga on 03-Nov-17.
//

#include "ThreadPool.h"
#include <thread>
#include <iostream>

void doNothing() {}

ThreadPool::ThreadPool(int nr_threads) : done(false) {
    if (nr_threads <= 0)
        thread_count = std::thread::hardware_concurrency();
    else
        thread_count = nr_threads;
    for (unsigned int i = 0; i < thread_count; ++i)
        //it pushes function which are executed from an implicitly created thread
        threads.emplace_back(&ThreadPool::worker_thread, this);
}

ThreadPool::~ThreadPool() {
    done = true;
    for (unsigned int i = 0; i < thread_count; ++i) pushTask(&doNothing);
    for (auto &th: threads)
        if (th.joinable())
            th.join();
}

void ThreadPool::worker_thread() {
    while (!done) {
        work_queue.get()(); //Get a function and call it
        workingThreads--;
        {
            std::unique_lock<std::mutex> lck(joinMutex);
            joinCV.notify_one();
        }
    }
}

void ThreadPool::join() {
    std::unique_lock<std::mutex> lck(joinMutex);
    while (workingThreads != 0) {
        joinCV.wait(lck);
    }
}