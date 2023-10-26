//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_CLIENTLOGIN_H
#define WORMS_TALLER_1_CLIENTLOGIN_H


#include <atomic>
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Thread/Thread.h"
#include "GamesProtected.h"
#include "../Protocol/ServerProtocol.h"

class ClientLogin : public Thread{
private:
    Socket sktPeer;
    GamesProtected& games;
    std::atomic<bool> isRunning;
    ServerProtocol serverProtocol;
public:
    ClientLogin(Socket socket, GamesProtected& aGames);

    void run() override;

    bool isDead() const;

    void stop();
};


#endif //WORMS_TALLER_1_CLIENTLOGIN_H
