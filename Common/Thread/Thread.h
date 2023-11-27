//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_THREAD_H
#define WORMS_TALLER_1_THREAD_H


#include <thread>
#include <iostream>
#include <atomic>

class Runnable {
 public:
        virtual void start() = 0;
        virtual void join() = 0;
        virtual void stop() = 0;
        virtual bool is_alive() const = 0;

        virtual ~Runnable() {}
};

class Thread : public Runnable {
 private:
        std::thread thread;

 protected:
        // Subclasses that inherit from Thread will have access to these
        // flags, mostly to control how Thread::run() will behave
        std::atomic<bool> _keep_running;
        std::atomic<bool> _is_alive;

 public:
        Thread() : _keep_running(true), _is_alive(false) {}

        void start() override;

        void join() override;

        void main();

        // Note: it is up to the subclass to make something meaningful to
        // really stop the thread. The Thread::run() may be blocked and/or
        // it may not read _keep_running.
        void stop() override {
            _keep_running = false;
        }

        bool is_alive() const override {
            return _is_alive;
        }

        virtual void run() = 0;
        virtual ~Thread() {}

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other) = delete;
        Thread& operator=(Thread&& other) = delete;
};

#endif  // WORMS_TALLER_1_THREAD_H
