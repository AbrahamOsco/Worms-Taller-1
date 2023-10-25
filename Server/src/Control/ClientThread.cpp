//
// Created by abraham on 23/10/23.
//

#include "ClientThread.h"
#include "ReceiverThread.h"
#include "SenderThread.h"
#include "ServerProtocol.h"

#include "../../../Common/DTO/LobbyAnswerDTO.h"


ClientThread::ClientThread(Socket sktPeer, size_t unIdThr, ProtectedGameRooms &gameRooms) : sktPeer(std::move(sktPeer)), idThread(unIdThr), gameRooms(gameRooms) {
    this->keepTalking = true;
    this->isAlive = true;
}


//Hilo Lobby. antes de lanzar el thread Receiver o el thread sender chequeo si el usuario va a crearse o unirse a una partida.


void ClientThread::run() {
    ServerProtocol serverProtocol(sktPeer);
    LobbyAnswerDTO lobyAnswer = serverProtocol.recvLobbyAnswer();
    if(lobyAnswer.getGameName().empty() && !serverProtocol.isAvailable() ){
        keepTalking = isAlive = false;
        return;
    }

    OperationType typeOperation = lobyAnswer.getOperationType();

    if(typeOperation == OperationType::CREATE_GAME){
        gameRooms.addGameRoomAndPlayer(lobyAnswer.getGameName(), lobyAnswer.getSelectedScenario(), 2, this);
    } else if (typeOperation == OperationType::JOIN_GAME ){
        gameRooms.addPlayer(lobyAnswer.getGameName(), this);
    }

    ReceiverThread receiverThread(sktPeer, keepTalking, isAlive, idThread);
    receiverThread.start();
    SenderThread senderThread(sktPeer, keepTalking, idThread);
    senderThread.start();

    senderThread.join();
    receiverThread.join();
}



bool ClientThread::isDead() const { return not isAlive; }

size_t ClientThread::getIdThread() const { return idThread; }


void ClientThread::kill() {
    keepTalking = false;
    sktPeer.totalClosure();
}

