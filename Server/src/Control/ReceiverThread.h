//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_RECEIVERTHREAD_H
#define WORMS_TALLER_1_RECEIVERTHREAD_H

#include <atomic>
#include "../../Common/Socket.h"
#include "../../Common/Thread/Thread.h"

class ReceiverThread : public Thread {
private:
    Socket& sktPeer;                         // cppcheck-suppress unusedStructMember
    std::atomic<bool>& keepTalking;          // cppcheck-suppress unusedStructMember
    std::atomic<bool>& isAlive;              // cppcheck-suppress unusedStructMember
    size_t& idThread;

public:

    ReceiverThread(Socket& aSkt, std::atomic<bool>& aKeepTalking, std::atomic<bool>& aIsAlive,
                   size_t& idThread);

    virtual void run() override;


    ~ReceiverThread() = default;

};


#endif //WORMS_TALLER_1_RECEIVERTHREAD_H
