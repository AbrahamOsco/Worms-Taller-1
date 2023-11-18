//
// Created by abraham on 26/10/23.
//

#include <string>
#include <iostream>
#include "Model.h"
#include "../../../../Common/DTO/PlayersDTO.h"

Model::Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters)
        : stage(scenarioName), players(stage.getIdsAndPositionsWorms(), parameters), world(aWorld), gameContactListener(&aWorld, &parameters), turns(players){
}

void Model::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players.addPlayer(playerName, idPlayer);
}

StageDTO Model::getStageDTO() const {

    return stage.getStageDTO();


}

std::vector<WormDTO> Model::getWormsDTO() const {
    try{

        return players.getWormsDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro  de getWormsDTO" << e.what() << "\n";
    }

}

PlayersDTO Model::getPlayersDTO() const {

    try{

        return players.getPlayersDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro de getPlayersDTO" << e.what() << "\n";
    }
}

StageDTO Model::startAndGetStageDTO() {
    players.assignWormsToPlayers();
    stage.addToTheWorld(&world);
    players.addToTheWorld(&world);
    turns.startATurn();
    return this->getStageDTO();
}

void Model::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft) {
    players.getCurrentPlayer().execute(aCommandDTO, timeLeft);
}

void Model::update() {
    players.update();
    turns.tryEndTurn();
}
void Model::subtractTime(){
    turns.subtractTime();
}

TurnDTO Model::getTurnDTO() const {
    try{

        return turns.getTurnDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro de TURNOS DTO" << e.what() << "\n";
    }


}

std::vector<WeaponsDTO> Model::getVecWeaponsDTO() const {
    try{

        return players.getVecWeaponsDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro de weaponsDTO" << e.what() << "\n";
    }
}

WeaponSightDTO Model::getWeaponSightDTO() {
    try{

        return players.getCurrentWorm()->getWeaponSightDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro de WEAPONSSIGHT DTO" << e.what() << "\n";
    }

}
ProjectilesDTO Model::getProjectilesDTO(){
    try{

        return players.getCurrentWorm()->getProjectilesDTO();
    }catch(std::exception& e){
        std::cerr << "Excepcion dentro PROJECTILESDTO de" << e.what() << "\n";
    }

}

void Model::tryAttackVariablePower() {
    players.getCurrentWorm()->tryAttackVariablePower();
}

int Model::getTimeLeft() const {
    return turns.getTimeLeft();
}




