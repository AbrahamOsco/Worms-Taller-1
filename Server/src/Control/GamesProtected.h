//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_GAMESPROTECTED_H
#define WORMS_TALLER_1_GAMESPROTECTED_H


#include <string>
#include <map>
#include <mutex>
#include "Engine.h"
#include "../../../Common/Socket/Socket.h"

class GamesProtected {
private:
    std::map<std::string, Engine*> games;

    std::mutex mtx;
public:
    GamesProtected();

    int createGameAndJoinPlayer(const std::string& gameName, Socket peerJugador, const size_t& idJugador);

};


#endif //WORMS_TALLER_1_GAMESPROTECTED_H
