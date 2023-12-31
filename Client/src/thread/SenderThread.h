//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_SENDERTHREAD_H
#define WORMS_TALLER_1_SENDERTHREAD_H


#include <memory>
#include <atomic>
#include "../protocol/ClientProtocol.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/Thread/Thread.h"

class SenderThread : public Thread {
 private:
    ClientProtocol& m_protocol;
    Queue<std::unique_ptr<Command>>& m_queue;
    std::atomic<bool>& m_running;

 public:
    SenderThread(ClientProtocol& protocol, Queue<std::unique_ptr<Command>>& queue, std::atomic<bool>& running);
    void run() override;
    void stop();
};


#endif  // WORMS_TALLER_1_SENDERTHREAD_H
