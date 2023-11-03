//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_ESTABLISHEDCONNECTIONS_H
#define WORMS_TALLER_1_ESTABLISHEDCONNECTIONS_H


#include <cstddef>
#include <map>
#include "../../../Common/Socket/Socket.h"
#include "ClientConnection.h"
#include "../../../Common/Queue/Queue.h"
#include "Command/Command.h"
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/PlayersIniDTO.h"

class EstablishedConnections {
private:
    std::map<size_t, ClientConnection> clientConnections;
    Queue<Command*> &commandQueueNB;
    Queue<WorldChangesDTO*>& worldChangesBQ;
public:

    EstablishedConnections(Queue<Command *> &aCommandQueueNB, Queue<WorldChangesDTO *>& aWorldChangesBQ);

    void addConnection(const size_t &idPlayer, Socket sktPeer);

    void start(const StageDTO &stageDTO, const PlayersIniDTO &playersIniDTO);

    void stop();

    void pushUpdate(const std::vector<PlayerDTO> &playersDTO);
};


#endif //WORMS_TALLER_1_ESTABLISHEDCONNECTIONS_H
