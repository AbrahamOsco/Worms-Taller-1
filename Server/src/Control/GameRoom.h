//
// Created by abraham on 24/10/23.
//

#ifndef WORMS_TALLER_1_GAMEROOM_H
#define WORMS_TALLER_1_GAMEROOM_H


#include <string>
#include <map>
#include "ClientThread.h"

class GameRoom {
private:
    std::string nameGameRoom;
    std::string nameScenario;
    size_t numberPlayerReq;
    size_t currentPlayers;
    std::map<size_t, ClientThread*> playersInHall;

public:
    explicit GameRoom(const std::string& nameGameRoom, const std::string& nameScenario, const size_t& numberPlayerReq);

    std::string getNameGameRoom() const;

    void addPlayer(ClientThread* clientThr);

    ~GameRoom() = default;

};


#endif //WORMS_TALLER_1_GAMEROOM_H
