//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_RECEIVERTHREAD_H
#define WORMS_TALLER_1_RECEIVERTHREAD_H

#include <memory>
#include <vector>
#include "../../../Common/Thread/Thread.h"
#include "../gameObject/GameObject.h"
#include "../protocol/ClientProtocol.h"
#include "../../../Common/Queue/Queue.h"

class ReceiverThread : public Thread {
 private:
    Queue<std::vector<std::unique_ptr<GameObject>>>& m_queue;
    ClientProtocol& m_protocol;
    std::atomic<bool>& m_running;

 public:
    ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue,
                    std::atomic<bool>& running);
    void run() override;
    void stop() override;
};


#endif  // WORMS_TALLER_1_RECEIVERTHREAD_H
