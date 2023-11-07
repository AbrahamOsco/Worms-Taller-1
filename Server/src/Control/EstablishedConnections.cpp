//
// Created by abraham on 28/10/23.
//

#include <stdexcept>
#include "EstablishedConnections.h"
#include "../../../Common/DTO/StageDTO.h"

EstablishedConnections::EstablishedConnections(Queue<Command *> &aCommandQueueNB, Queue<std::unique_ptr<SnapShot>>& aWorldChangesBQ)
        : commandQueueNB(aCommandQueueNB), worldChangesBQ(aWorldChangesBQ) {

}

void EstablishedConnections::addConnection(const size_t &idPlayer, Socket sktPeer) {
    if (clientConnections.count(idPlayer) > 0){
        throw std::runtime_error(" [EstablishedConnections]: El id del cliente ya ha sido agregado \n");
    }
    // uso emplace para no realize copias sino lo cree ahi mismo.
    clientConnections.emplace(idPlayer, ClientConnection(idPlayer, sktPeer, commandQueueNB, worldChangesBQ) );
}

void EstablishedConnections::start(const StageDTO &stageDTO) {
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

void EstablishedConnections::pushUpdate(const std::vector<PlayerDTO> &playersDTO) {
    for (auto &element : clientConnections) {   // Le digo a todos mis clientConnection start
        element.second.pushUpdates(playersDTO);
    }
}


