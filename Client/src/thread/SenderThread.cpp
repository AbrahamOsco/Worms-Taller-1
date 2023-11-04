//
// Created by riclui on 31/10/23.
//

#include "SenderThread.h"

SenderThread::SenderThread(ClientProtocol &protocol, Queue<std::unique_ptr<Command>> &queue) : m_protocol(protocol), m_queue(queue){}

void SenderThread::run() {
    while (running) {
        try {
            std::unique_ptr<Command> action;
            action = m_queue.move_pop();
            action->execute(m_protocol);
        } catch (ClosedQueue & closedQueue) {
            running = false;
        }
    }
}

void SenderThread::stop() {
    running = false;
    m_queue.close();
}
