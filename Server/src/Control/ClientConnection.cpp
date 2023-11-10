//
// Created by abraham on 28/10/23.
//

#include "ClientConnection.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/PlayersDTO.h"
//commandsQueueNB(UINT_MAX - 1)
ClientConnection::ClientConnection(const size_t &idPlayer, Socket aSktPeer, Queue<std::unique_ptr<CommandDTO>> &aCommandQueueNB) :
        idPlayer(idPlayer), sktPeer(std::move(aSktPeer)), commandQueueNB(aCommandQueueNB),
        snapShotQueueB(std::make_unique<Queue<std::unique_ptr<SnapShot>>>(UINT_MAX -1)) {
}


void ClientConnection::start(const StageDTO &stageDTO) {        //Lanzo los threads sender y receiver
    // Aca envio el byte START_GAME y el stage completo antes de lanzar los thread receiver y sender.
    ServerProtocol serverProtocol(sktPeer);
    serverProtocol.sendANumberByte(START_GAME);
    serverProtocol.sendStage(stageDTO);
    receiver = std::thread(&ClientConnection::runReceiver, this);
    sender = std::thread(&ClientConnection::runSender, this);
}

void ClientConnection::join() {
    sender.join();
    receiver.join();
}

// enviamos snapShots al cliente (actualizaciones del mundo)
void ClientConnection::runSender() {
    try{
        ServerProtocol serverProtocol(sktPeer);
        std::unique_ptr<SnapShot> aSnapShot = nullptr;
        while( (aSnapShot = snapShotQueueB->move_pop()) ){
            serverProtocol.sendSnapShot(aSnapShot);
        }
    }catch (const std::exception& e ){
        sktPeer.totalClosure();
        sktPeer.close();
    }
}

void ClientConnection::runReceiver() {
    ServerProtocol serverProtocol(sktPeer);
    while(serverProtocol.isAvailable()){
        std::unique_ptr<CommandDTO> aCommandDTO = std::make_unique<CommandDTO>(serverProtocol.recvCommandDTO());
        commandQueueNB.move_try_push(std::move(aCommandDTO));  // usamos una cola no bloqueante es -> try_push
    }
}

void ClientConnection::stop() {
    snapShotQueueB->close();
}

void ClientConnection::pushSnapShot(const std::vector<WormDTO> &vecWormsDTO, const PlayersDTO &playersDTO,
                                    const std::vector<WeaponsDTO> &vecWeaponsDTO) {
    //aca en cada client connectio nago el unicast.
    WeaponsDTO selectWeaponsDTO;
    for(auto& aWeaponsDTO : vecWeaponsDTO){
        if(aWeaponsDTO.getIdPlayer() == this->idPlayer){
            selectWeaponsDTO = aWeaponsDTO;
            break;
        }
    }
    std::unique_ptr<SnapShot> aSnapShot = std::make_unique<SnapShot>(vecWormsDTO, playersDTO, selectWeaponsDTO);
    this->snapShotQueueB->move_push(std::move(aSnapShot));
}

