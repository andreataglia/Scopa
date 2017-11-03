cmake_minimum_required(VERSION 3.8)
project(Scopa)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp src/Card.cpp src/Card.h src/Game.cpp src/Game.h src/Deck.cpp src/Deck.h src/State.cpp src/State.h src/ThreadPool.cpp src/ThreadPool.h src/SynchronizedQueue.h src/SynchronizedQueue.cpp)

add_executable(Scopa ${SOURCE_FILES} src/SynchronizedQueue.h src/SynchronizedQueue.cpp)