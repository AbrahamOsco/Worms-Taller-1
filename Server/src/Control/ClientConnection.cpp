//
// Created by abraham on 28/10/23.
//

#include "ClientConnection.h"
ClientConnection::ClientConnection(const size_t &idPlayer, Socket& aSktPeer, Queue<Command *> &aCommandQueueNB, Queue<WorldChangesDTO*>& aWorldChangesNB) :
        idPlayer(idPlayer), sktPeer(std::move(aSktPeer)), commandQueueNB(aCommandQueueNB), worldChangesNB(aWorldChangesNB){

}


void ClientConnection::start() {        //Lanzo los threads sender y receiver
    receiver = std::thread(&ClientConnection::runReceiver, this);
    sender = std::thread(&ClientConnection::runSender, this);
}


void ClientConnection::stop() {
    sktPeer.totalClosure();
}

void ClientConnection::join() {
    sender.join();
    receiver.join();

}

void ClientConnection::runSender() {


}

void ClientConnection::runReceiver() {

}

void ClientConnection::pushUpdates() {
    WorldChangesDTO* worldChangesDto = new WorldChangesDTO();
    worldChangesNB.push(worldChangesDto);
}

