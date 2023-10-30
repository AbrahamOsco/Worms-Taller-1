//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_CLIENTCONNECTION_H
#define WORMS_TALLER_1_CLIENTCONNECTION_H


#include <cstddef>
#include <thread>
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Queue/Queue.h"
#include "Command/Command.h"
#include "../../../Common/DTO/WorldChangesDTO.h"
#include "../../../Common/DTO/StageDTO.h"

class ClientConnection {
private:
    size_t idPlayer;
    Socket sktPeer;
    std::thread sender;
    std::thread receiver;
    Queue<Command*> &commandQueueNB;
    Queue<WorldChangesDTO*>& worldChangesNB;
public:
    ClientConnection(const size_t &idPlayer, Socket &aSktPeer, Queue<Command *> &aCommandQueueNB, Queue<WorldChangesDTO*>& aWorldChangesNB);

    //ClientConnection(const size_t &idPlayer, Socket& aSktPeer, Queue<Command *> &aCommandQueueNB);

    void runSender();

    void runReceiver();

    void start(const StageDTO &stageDTO);

    void stop();

    void join();

    void pushUpdates();
};


#endif //WORMS_TALLER_1_CLIENTCONNECTION_H
