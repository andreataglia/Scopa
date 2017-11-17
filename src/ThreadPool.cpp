//
// Created by Spranga on 03-Nov-17.
//

#include "ThreadPool.h"
#include <thread>
#include <iostream>

std::vector<int> doNothing() {return std::vector<int>{0};}

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
    for (unsigned int i = 0; i < thread_count; ++i){
      packaged_task<std::vector<int>()> tsk(&doNothing);   
      work_queue.put(tsk);
    }
    for (auto &th: threads)
        if (th.joinable())
            th.join();
}

void ThreadPool::pushTask(std::packaged_task<std::vector<int>()> func) {
        work_queue.put(func);
        workingThreads++;
}

void ThreadPool::worker_thread() {
    while (!done) {
        auto task = work_queue.get();
        future<std::vector<int>> fut = task.get_future();
        task();
        std::vector<int> v = fut.get();
        
        {
            std::unique_lock<std::mutex> lck(resultsMutex);
            simulationResults.push_back(v[0]);
            simulationResults.push_back(v[1]);
        }

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

std::vector<int> ThreadPool::getResults(){
    join();
    auto temp = simulationResults;
    simulationResults.clear();
    return temp;
}