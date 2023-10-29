//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_MODEL_H
#define WORMS_TALLER_1_MODEL_H

#include <cstddef>
#include "Player.h"
#include "Stage.h"
#include <map>
#include <string>

class Model {
private:
    size_t numberPlayerReq;
    size_t currentPlayers;
    bool finishedGame;
    std::map<size_t, Player> players;
    Stage stage;

public:
    Model();
    void addPlayer(const std::string &playerName, const size_t &idPlayer);

};


#endif //WORMS_TALLER_1_MODEL_H
