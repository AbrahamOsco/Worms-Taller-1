//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"

Model::Model() {
}


void Model::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players.addPlayer(playerName, idPlayer);
}

StageDTO Model::getStageDTO() const {
    return stage.getStageDTO();
}

std::vector<PlayerDTO> Model::getPlayersDTO() const {
    return players.getPlayersDTO();
}


