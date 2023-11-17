//
// Created by riclui on 31/10/23.
//

#include "SenderThread.h"

SenderThread::SenderThread(ClientProtocol &protocol, Queue<std::unique_ptr<Command>> &queue, std::atomic<bool>& running) : m_protocol(protocol), m_queue(queue), m_running(running){}

void SenderThread::run() {
    while (m_running) {
        try {
            std::unique_ptr<Command> action;
            action = m_queue.move_pop();
            action->execute(m_protocol);
        } catch (ClosedQueue & closedQueue) {
            m_running = false;
        }
    }
}

void SenderThread::stop() {
    m_running = false;
    m_queue.close();
}
