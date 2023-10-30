//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"

Model::Model() {
}


void Model::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    this->players[idPlayer] = Player(playerName, idPlayer);
}


