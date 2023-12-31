//
// Created by abraham on 26/10/23.
//

#include <string>
#include <iostream>
#include <vector>
#include "Model.h"
#include "../../../../Common/DTO/PlayersDTO.h"

Model::Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters)
        : stage(scenarioName), players(stage.getIdsAndPositionsWorms(), parameters),
        world(aWorld), gameContactListener(&aWorld, &parameters), turns(players, parameters, &world) {
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

void Model::execute(const CommandDTO &aCommandDTO, const int &timeLeft) {
    if ( aCommandDTO.getTypeCommand() == MIN_LIFE ) {
        players.setLifeAllWorm(1.0f);
    } else if (aCommandDTO.getTypeCommand() == MAX_LIFE) {
        players.setLifeAllWorm(200.0f);
    } else {
        players.getCurrentPlayer().execute(aCommandDTO, timeLeft);
    }
}

void Model::update() {
    players.update();
    turns.tryEndTurn();
}

void Model::subtractTime() {
    turns.subtractTime();
}

void Model::tryToChangeFocus() {
    turns.tryToChangeFocus();
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
ProjectilesDTO Model::getProjectilesDTO() {
    return players.getCurrentWorm()->getProjectilesDTO();
}

std::vector<ProvisionDTO> Model::getVecProvisionDTO() {
    return this->turns.getVecProvisionDTO();
}


void Model::tryAttackVariablePower() {
    players.getCurrentWorm()->tryAttackVariablePower();
}

int Model::getTimeLeft() const {
    return turns.getTimeLeft();
}

bool Model::onlyOnePlayerExits() {
    return players.onlyExistsOnePlayer();
}

std::vector<EndGameDTO> Model::getVecEndGameDTO() {
    return players.getVecEndGameDTO();
}

void Model::destroyAllBodys() {
    world.ClearForces();
    b2Body* listBodys = world.GetBodyList();
    while (listBodys) {
        b2Body* bodyAct = listBodys;
        listBodys = bodyAct->GetNext();
        world.DestroyBody(bodyAct);
    }
}



