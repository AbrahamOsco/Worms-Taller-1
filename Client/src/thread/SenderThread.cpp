//
// Created by riclui on 31/10/23.
//

#include "SenderThread.h"

SenderThread::SenderThread(ClientProtocol &protocol, Queue<std::unique_ptr<Command>> &queue) : m_protocol(protocol), m_queue(queue), m_isRunning(true){}

void SenderThread::run() {
    while (m_isRunning) {
        try {
            std::unique_ptr<Command> action;
            action = m_queue.move_pop();
            action->execute(m_protocol);
        } catch (ClosedQueue & closedQueue) {
            m_isRunning = false;
        }
    }
}

void SenderThread::stop() {
    m_isRunning = false;
    m_queue.close();
}
