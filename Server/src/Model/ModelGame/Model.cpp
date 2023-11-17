//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"
#include "../../../../Common/DTO/PlayersDTO.h"

Model::Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters)
        : stage(scenarioName), players(stage.getIdsAndPositionsWorms(), parameters), world(aWorld), gameContactListener(&aWorld), turns(players){
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

PlayersDTO Model::getPlayersDTO() const {
    return players.getPlayersDTO();
}

StageDTO Model::startAndGetStageDTO() {
    players.assignWormsToPlayers();
    stage.addToTheWorld(&world);
    players.addToTheWorld(&world);
    turns.startATurn();
    return this->getStageDTO();
}

void Model::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft) {
    players.getCurrentWorm()->execute(aCommandDTO, timeLeft);
}

void Model::update() {
    players.update();
    turns.tryEndTurn();
}
void Model::subtractTime(){
    turns.subtractTime();
}

TurnDTO Model::getTurnDTO() const {
    return turns.getTurnDTO();
}

std::vector<WeaponsDTO> Model::getVecWeaponsDTO() const {
    return players.getVecWeaponsDTO();
}

WeaponSightDTO Model::getWeaponSightDTO() {
    return players.getCurrentWorm()->getWeaponSightDTO();
}
ProjectilesDTO Model::getProjectilesDTO(){
    return players.getCurrentWorm()->getProjectilesDTO();
}

void Model::tryAttackVariablePower() {
    players.getCurrentWorm()->tryAttackVariablePower();
}

int Model::getTimeLeft() const {
    return turns.getTimeLeft();
}




