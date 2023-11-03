//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"
#include "../../../Common/DTO/PlayersIniDTO.h"
#define GRAVEDAD -10.0f

Model::Model(const std::string &scenarioName) : stage(scenarioName), players(stage.getIdsAndPositionsWorms()), world( b2Vec2(0.0f, GRAVEDAD) ) {
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
    addBeamsToWorld();
    addWormsToWorld();
}

void Model::addBeamsToWorld() {
    stage.addBeamsToWorld(&world);
}

void Model::addWormsToWorld() {

}


