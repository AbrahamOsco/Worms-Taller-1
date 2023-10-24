//
// Created by abraham on 23/10/23.
//

#include "SenderThread.h"



SenderThread::SenderThread(Socket &aSkt, std::atomic<bool> &aKeepTalking, size_t& unIdThread) :sktPeer(aSkt),
                                    keepTalking(aKeepTalking), idThread(unIdThread)  {

}

void SenderThread::run() {

}
