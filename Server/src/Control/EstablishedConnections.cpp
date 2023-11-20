//
// Created by abraham on 28/10/23.
//

#include <stdexcept>
#include "EstablishedConnections.h"
#include "../../../Common/DTO/TurnDTO.h"


EstablishedConnections::EstablishedConnections(Queue<std::unique_ptr<CommandDTO>> &aCommandQueueNB)
        : commandQueueNB(aCommandQueueNB) {

}

void EstablishedConnections::addConnection(const size_t &idPlayer, Socket sktPeer) {
    if (clientConnections.count(idPlayer) > 0){
        throw std::runtime_error(" [EstablishedConnections]: El id del cliente ya ha sido agregado \n");
    }
    // uso emplace para no realize copias sino lo cree ahi mismo.
    //clientConnections[idPlayer] = std::make_unique<ClientConnection>(idPlayer, std::move(sktPeer), commandQueueNB) ;
    clientConnections.emplace(idPlayer, ClientConnection(idPlayer, std::move(sktPeer), commandQueueNB) );
}

void EstablishedConnections::start(StageDTO &stageDTO) {
    for (auto &element : clientConnections) {   // Le digo a todos mis clientConnection start
        element.second.start(stageDTO);
    }
}

void EstablishedConnections::stop() {
    for (auto &element : clientConnections) {
        element.second.stop();
        element.second.join();
    }
    clientConnections.clear();
}


// Todos los clientes pushean el vector de wormsDTO que envio a su propio queue cada una asi visualizan todos los worms.
// Esto es un broadcast. para todos los clientes.
void EstablishedConnections::pushSnapShot(const std::vector<WormDTO> &vectorWormsDTO, const PlayersDTO &playersDTO,
                                          const std::vector<WeaponsDTO> &vecWeaponsDTO,
                                          const WeaponSightDTO &weaponSightDTO,
                                          const ProjectilesDTO &projectilesDTO, TurnDTO turnDTO,
                                          const std::vector<ProvisionDTO> &vecProvisionDTO) {
    for (auto &element : clientConnections) {
        element.second.pushSnapShot(vectorWormsDTO, playersDTO, vecWeaponsDTO, weaponSightDTO, projectilesDTO, turnDTO,
                                    vecProvisionDTO);
    }
}

void EstablishedConnections::pushVecEndGame(const std::vector<EndGameDTO> &vecEndGameDTO) {
    for (auto &element : clientConnections) {
        element.second.pushEndGame(vecEndGameDTO);
    }
}


