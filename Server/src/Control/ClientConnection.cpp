//
// Created by abraham on 28/10/23.
//

#include "ClientConnection.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/PlayersIniDTO.h"

ClientConnection::ClientConnection(const size_t &idPlayer, Socket& aSktPeer, Queue<Command *> &aCommandQueueNB, Queue<WorldChangesDTO*>& aWorldChangesBQ) :
        idPlayer(idPlayer), sktPeer(std::move(aSktPeer)), commandQueueNB(aCommandQueueNB), worldChangesBQ(aWorldChangesBQ){

}


void ClientConnection::start(const StageDTO &stageDTO, const PlayersIniDTO &playersIniDTO) {        //Lanzo los threads sender y receiver
    // Aca envio el byte START_GAME y el stage completo antes de lanzar los thread receiver y sender.
    ServerProtocol serverProtocol(sktPeer);
    serverProtocol.sendANumberByte(START_GAME);
    serverProtocol.sendStage(stageDTO);
    serverProtocol.sendPlayersIni(playersIniDTO);
    receiver = std::thread(&ClientConnection::runReceiver, this);
    sender = std::thread(&ClientConnection::runSender, this);
}

void ClientConnection::join() {
    sender.join();
    receiver.join();

}

void ClientConnection::runSender() {
    try{
        WorldChangesDTO* aWorldChange = NULL;
        while((aWorldChange = worldChangesBQ.pop())){
            //protocolo.sendGusanos(aWorldChange.getGusanos()); // todos los players se ennteran de la salud, posicion de los gusanos.
            //protocolo.sendDataPlayer(aWorldChange.getPlayer(this->idPlayer)) // enviamos un unicast (filtro por id) del player - municiones a cada player correspondiente).
        }
    }catch (const std::exception& e ){
        sktPeer.totalClosure();
        sktPeer.close();
    }
}

void ClientConnection::runReceiver() {

}

void ClientConnection::stop() {
    worldChangesBQ.close();
}


void ClientConnection::pushUpdates(const std::vector<PlayerDTO> &vector) {
    WorldChangesDTO* worldChangesDto = new WorldChangesDTO();
    worldChangesBQ.push(worldChangesDto);
}

