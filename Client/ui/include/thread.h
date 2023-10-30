#ifndef THREAD_H_
#define THREAD_H_

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
        Thread () : _keep_running(true), _is_alive(false) {}

        void start() override {
            _is_alive = true;
            _keep_running = true;
            thread = std::thread(&Thread::main, this);
        }

        void join() override {
            thread.join();
        }

        void main() {
            try {
                this->run();
            } catch(const std::exception &err) {
                std::cerr << "Unexpected exception: " << err.what() << "\n";
            } catch(...) {
                std::cerr << "Unexpected exception: <unknown>\n";
            }

            _is_alive = false;
        }

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

#endif
