//
// Created by riclui on 31/10/23.
//

#include "SenderThread.h"

SenderThread::SenderThread(ClientProtocol &protocol, Queue<std::unique_ptr<Command>> &queue) : m_protocol(protocol), m_queue(queue){}

void SenderThread::run() {
    /*while (running) {
        std::unique_ptr<Command> action;
        action = m_queue.pop();
    }*/
}

void SenderThread::stop() {
    running = false;
    m_queue.close();
}
