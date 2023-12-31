//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_CLIENTLOGIN_H
#define WORMS_TALLER_1_CLIENTLOGIN_H


#include <atomic>
#include <string>
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

    void execute(const ResponseInitialStateDTO &response, const std::string &playerName);

    ~ClientLogin() = default;
};


#endif  // WORMS_TALLER_1_CLIENTLOGIN_H
