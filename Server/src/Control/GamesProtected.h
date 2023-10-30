//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_GAMESPROTECTED_H
#define WORMS_TALLER_1_GAMESPROTECTED_H


#include <string>
#include <map>
#include <mutex>
#include <vector>
#include "Engine.h"
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"

// Monitor tiene el recurso Engine(compartido por jugaodres q estan en una misma partida y el mutex.

class GamesProtected {
private:
    std::map<std::string, Engine*> games;

    std::mutex mtx;
public:
    GamesProtected();

    int createGameAndAddPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName);

    int addPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName);


    void printRooms();

    std::vector<std::string> getScenarios();

    std::vector<RoomDTO> getAvailableRooms();
};


#endif //WORMS_TALLER_1_GAMESPROTECTED_H
