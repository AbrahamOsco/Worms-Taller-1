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
    std::map<std::string, std::unique_ptr<Engine>> games;
    std::vector<std::string> nameScenarios;
    std::vector<std::size_t> maxNumbersWorms;
    std::mutex mtx;

public:
    GamesProtected();

    int createGameAndAddPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName);

    int addPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName);


    void printRooms();

    std::vector<std::string> getScenarios();

    std::vector<std::size_t> getMaxNumbersWorms();

    std::vector<RoomDTO> getAvailableRooms();

    void stop();

};


#endif //WORMS_TALLER_1_GAMESPROTECTED_H
