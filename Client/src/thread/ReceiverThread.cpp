//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue) : m_protocol(protocol), m_queue(queue), m_running(true) {}

void ReceiverThread::run() {
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    LoaderParams params1(512, 384, 60, 60, "player");
    gameObjects.push_back(std::make_unique<Worm>(params1));
    m_queue.move_try_push(std::move(gameObjects));
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
