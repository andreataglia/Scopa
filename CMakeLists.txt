cmake_minimum_required(VERSION 3.8)
project(Scopa)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp src/Card.cpp src/Card.h src/Deck.cpp src/Deck.h)

add_executable(Scopa ${SOURCE_FILES})