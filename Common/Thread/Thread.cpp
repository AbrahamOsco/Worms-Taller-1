//
// Created by abraham on 23/10/23.
//

#include <iostream>
#include "Thread.h"

void Thread::start() {
    this->thread = std::thread(&Thread::main, this);
}

void Thread::main() {
    try{
        run();
    } catch( const std::exception& e ){
        std::cerr << e.what() << "\n";
    } catch ( ... ){
        std::cerr << "Unknown error in Thread\n";
    }
}

void Thread::join() {
    thread.join();
}
