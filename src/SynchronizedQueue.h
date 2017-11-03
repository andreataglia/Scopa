//
// Created by Spranga on 03-Nov-17.
//

#ifndef SYNC_QUEUE_H_
#define SYNC_QUEUE_H_
#include <list>
#include <mutex>
#include <condition_variable>

template<typename T>
class SynchronizedQueue {

public:
    SynchronizedQueue(){};

    void put(const T &data);

    T get();

    size_t size();

private:
    SynchronizedQueue(const SynchronizedQueue &) = delete;

    SynchronizedQueue &operator=(const SynchronizedQueue &)= delete;

    std::list<T> queue;
    std::mutex myMutex;
    std::condition_variable myCv;
};

#endif // SYNC_QUEUE_H_