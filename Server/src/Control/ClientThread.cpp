//
// Created by abraham on 23/10/23.
//

#include "ClientThread.h"
#include "ReceiverThread.h"
#include "SenderThread.h"


ClientThread::ClientThread(Socket sktPeer, size_t unIdThr) : sktPeer(std::move(sktPeer)),
                                                             keepTalking(true), isAlive(true), idThread(unIdThr) {
}


void ClientThread::run() {
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
