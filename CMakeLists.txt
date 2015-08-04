cmake_minimum_required(VERSION 3.1)
project(SkelMUD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    SkelMUD/Connection.cpp
    SkelMUD/Connection.h
    SkelMUD/Entity.cpp
    SkelMUD/Entity.h
    SkelMUD/File.cpp
    SkelMUD/File.h
    SkelMUD/Game.cpp
    SkelMUD/Game.h
    SkelMUD/Logger.cpp
    SkelMUD/Logger.h
    SkelMUD/Network.cpp
    SkelMUD/Network.h
    SkelMUD/Planet.cpp
    SkelMUD/Planet.h
    SkelMUD/Player.cpp
    SkelMUD/Player.h
    SkelMUD/Sender.cpp
    SkelMUD/Sender.h
    SkelMUD/SkelMUD.cpp
    SkelMUD/TextProcessor.cpp
    SkelMUD/TextProcessor.h
    SkelMUD/Thread.cpp
    SkelMUD/Thread.h
    SkelMUD/Tokenizer.cpp
    SkelMUD/Tokenizer.h
    SkelMUD/Utils.cpp
    SkelMUD/Utils.h)

add_executable(SkelMUD ${SOURCE_FILES} SkelMUD/SkelMUD.cpp)
FIND_PACKAGE(Threads)
# FIND_PACKAGE(Threads) sets the following:
# CMAKE_THREAD_LIBS_INIT        - the thread library to link into an application (-lpthread )
# CMAKE_USE_SPROC_INIT          - are we using sproc?
# CMAKE_USE_WIN32_THREADS_INIT  - are we using WIN32 threads
# CMAKE_USE_PTHREADS_INIT       - are we using pthreads
# CMAKE_HP_PTHREADS_INIT        - are we using hp pthreads

TARGET_LINK_LIBRARIES(SkelMUD ${CMAKE_THREAD_LIBS_INIT})