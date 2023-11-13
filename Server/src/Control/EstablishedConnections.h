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
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/WeaponsDTO.h"
#include "../../../Common/DTO/WeaponSightDTO.h"

class EstablishedConnections {
private:
    std::map<size_t, ClientConnection> clientConnections;
    Queue<std::unique_ptr<CommandDTO>> &commandQueueNB;
public:

    EstablishedConnections(Queue<std::unique_ptr<CommandDTO>>& aCommandQueueNB);

    void addConnection(const size_t &idPlayer, Socket sktPeer);

    void start(const StageDTO &stageDTO);

    void stop();

    void pushSnapShot(const std::vector<WormDTO> &vectorWormsDTO, const PlayersDTO &playersDTO,
                      const std::vector<WeaponsDTO> &vecWeaponsDTO, const WeaponSightDTO &weaponSightDTO);


};


#endif //WORMS_TALLER_1_ESTABLISHEDCONNECTIONS_H
