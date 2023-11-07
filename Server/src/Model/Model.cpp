//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"
#include "../../../Common/DTO/PlayersIniDTO.h"

Model::Model(const std::string &scenarioName, b2World &aWorld) : stage(scenarioName), players(stage.getIdsAndPositionsWorms()), world(aWorld) {
}

void Model::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players.addPlayer(playerName, idPlayer);
}

StageDTO Model::getStageDTO() const {
    return stage.getStageDTO();
}

std::vector<WormDTO> Model::getWormsDTO() const {
    return players.getWormsDTO();
}

void Model::start() {
    players.assignWormsToPlayers();
    stage.addToTheWorld(&world);
    players.addToTheWorld(&world);
}

}



