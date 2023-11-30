//Lanza los threads
// Created by abraham on 23/10/23.
//

#include <iostream>
#include "Thread.h"
void Thread::start() {
            _is_alive = true;
            _keep_running = true;
            thread = std::thread(&Thread::main, this);
}

void Thread::main() {
            try {
                this->run();
            } catch(const std::exception &err) {
                std::cerr << "Unexpected exception: " << err.what() << "\n";
            } catch(...) {
                std::cerr << "Unexpected exception: <unknown>\n";
            }

            _is_alive = false;
        }

void Thread::join() {
    thread.join();
}
