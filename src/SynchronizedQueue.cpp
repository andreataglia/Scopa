//
// Created by Matteo Sinico on 03/11/17.
//
#include "SynchronizedQueue.h"

/*template<typename T>
SynchronizedQueue<T> synchronizedQueue (){}*/

template<typename T>
void SynchronizedQueue<T>::put(const T& data) {
    std::unique_lock<std::mutex> lck(myMutex);
    queue.push_back(data);
    myCv.notify_one();
}

template<typename T>
T SynchronizedQueue<T>::get() {
    std::unique_lock<std::mutex> lck(myMutex);
    while(queue.empty())
        myCv.wait(lck);
    T result=queue.front();
    queue.pop_front();
    return result;
}

int SynchronizedQueue::size() {
    std::unique_lock<std::mutex> lck(myMutex);
    return queue.size();
}
