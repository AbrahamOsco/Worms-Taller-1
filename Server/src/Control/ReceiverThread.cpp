//
// Created by abraham on 23/10/23.
//

#include "ReceiverThread.h"

ReceiverThread::ReceiverThread(Socket &aSkt, std::atomic<bool> &aKeepTalking, std::atomic<bool> &aIsAlive, size_t& idThread)
                                :sktPeer(aSkt), keepTalking(aKeepTalking), isAlive(aIsAlive), idThread(idThread){

}

void ReceiverThread::run(){

}


