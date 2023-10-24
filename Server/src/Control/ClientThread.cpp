//
// Created by abraham on 23/10/23.
//

#include "ClientThread.h"
#include "ReceiverThread.h"
#include "SenderThread.h"
#include "ServerProtocol.h"

#include "../../Common/DTO/LobbyAnswerDTO.h"


ClientThread::ClientThread(Socket sktPeer, size_t unIdThr) : sktPeer(std::move(sktPeer)),
                                                             keepTalking(true), isAlive(true), idThread(unIdThr) {
}

//Hilo Lobby. antes de lanzar el thread Receiver o el thread sender chequeo si el usuario va a crearse o unirse a una partida.

void ClientThread::run() {
    ServerProtocol serverProtocol(sktPeer);

    //Primer recv del server es la respuesta del lobby
    LobbyAnswerDTO lobyAnswer = serverProtocol.recvLobbyAnswer();
    if(lobyAnswer.getGameName().empty() && !serverProtocol.isAvailable() ){
        keepTalking = isAlive = false;
        return;
    }

    OpType typeOperation = lobyAnswer.getOperationType();
    if(typeOperation == OpType::CREATE_GAME){
        // Si esta creando un game creamos una partida con el nombre que pidio.
    } else if (typeOperation == OpType::JOIN_GAME ){
        // Si SE esta uniendo a un ame obtenemos el game de la partida y lo unimos.
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
