//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_SENDERTHREAD_H
#define WORMS_TALLER_1_SENDERTHREAD_H

#include <atomic>
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Thread/Thread.h"

class SenderThread : public Thread {
private:
    Socket& sktPeer;                         // cppcheck-suppress unusedStructMember
    std::atomic<bool>& keepTalking;          // cppcheck-suppress unusedStructMember
    size_t& idThread;                         // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    //
    SenderThread(Socket& aSkt, std::atomic<bool>& aKeepTalking, size_t& unIdThread);

    //  Pre: -.
    //  Post: ---
    virtual void run() override;

    ~SenderThread() = default;

};


#endif //WORMS_TALLER_1_SENDERTHREAD_H
