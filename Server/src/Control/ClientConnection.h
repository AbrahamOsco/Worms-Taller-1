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
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/PlayersIniDTO.h"
#include "../Model/SnapShot.h"

class ClientConnection {
private:
    size_t idPlayer;
    Socket sktPeer;
    std::thread sender;
    std::thread receiver;
    Queue<Command*> &commandQueueNB;
    Queue<std::unique_ptr<SnapShot>>& worldChangesBQ;
public:
    ClientConnection(const size_t &idPlayer, Socket &aSktPeer, Queue<Command *> &aCommandQueueNB, Queue<std::unique_ptr<SnapShot>>& aWorldChangesBQ);

    //ClientConnection(const size_t &idPlayer, Socket& aSktPeer, Queue<Command *> &aCommandQueueNB);

    void runSender();

    void runReceiver();

    void start(const StageDTO &stageDTO);

    void stop();

    void join();

    void pushUpdates(const std::vector<PlayerDTO> &vector);
};


#endif //WORMS_TALLER_1_CLIENTCONNECTION_H
