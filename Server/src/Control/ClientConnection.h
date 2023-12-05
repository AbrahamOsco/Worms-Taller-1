//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_CLIENTCONNECTION_H
#define WORMS_TALLER_1_CLIENTCONNECTION_H


#include <cstddef>
#include <thread>
#include <memory>
#include <vector>
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/PlayersDTO.h"
#include "../../../Common/DTO/SnapShot.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/WeaponsDTO.h"
#include "../../../Common/DTO/WeaponSightDTO.h"
#include "../../../Common/DTO/ProjectilesDTO.h"
#include "../../../Common/DTO/TurnDTO.h"
#include "../../../Common/DTO/EndGameDTO.h"
#include "../../../Common/DTO/ProvisionDTO.h"

class ClientConnection {
 private:
    size_t idPlayer;
    Socket sktPeer;
    std::thread sender;
    std::thread receiver;
    Queue<CommandDTO> &commandQueueNB;
    std::unique_ptr<Queue<std::unique_ptr<SnapShot>>> snapShotQueueB;  // Debido a que uso un emplaceBac en EstablishedConnections no me permite hacer una Queue a secas.
 public:
    ClientConnection(const size_t &idPlayer, Socket  aSktPeer, Queue<CommandDTO> &aCommandQueueNB);

    void runSender();

    void runReceiver();

    void start(StageDTO &stageDTO);

    void stop();

    void join();

    void pushSnapShot(const std::vector<WormDTO> &vecWormsDTO, const PlayersDTO &playersDTO,
                      const std::vector<WeaponsDTO> &vecWeaponsDTO, const WeaponSightDTO &weaponSightDTO,
                      const ProjectilesDTO &projectilesDTO, TurnDTO turnDTO,
                      const std::vector<ProvisionDTO> &vecProvisionDTO);

    void pushEndGame(const std::vector<EndGameDTO> &vecEndGameDTO);
};


#endif  // WORMS_TALLER_1_CLIENTCONNECTION_H
