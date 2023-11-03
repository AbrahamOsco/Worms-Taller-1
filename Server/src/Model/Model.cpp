//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"
#include "../../../Common/DTO/PlayersIniDTO.h"

Model::Model(const std::string &scenarioName) : stage(scenarioName), players(stage.getIdsAndPositionsWorms()) {

}


void Model::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players.addPlayer(playerName, idPlayer);
}

StageDTO Model::getStageDTO() const {
    return stage.getStageDTO();
}

PlayersIniDTO Model::getPlayersDTO() const {
    return PlayersIniDTO(players.getPlayersDTO());
}

void Model::start() {
    players.assignWormsToPlayers();
}



