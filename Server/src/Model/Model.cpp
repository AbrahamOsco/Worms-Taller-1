//
// Created by abraham on 26/10/23.
//

#include <string>
#include "Model.h"
#include "../../../Common/DTO/PlayersDTO.h"

Model::Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters)
        : stage(scenarioName), players(stage.getIdsAndPositionsWorms(), parameters), world(aWorld) {
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


void Model::start() {
    players.assignWormsToPlayers();
    stage.addToTheWorld(&world);
    players.addToTheWorld(&world);
    idPlayerWormCurrent = players.getIdPlayerWormCurrent() ;
}

void Model::execute(std::unique_ptr<CommandDTO> &aCommandDTO) {
    if(aCommandDTO->getTypeCommand() == TypeCommand::LEFT_CMD ){
        players.leftWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::RIGHT_CMD ){
        players.rightWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_BACK_CMD){
        players.jumpBackWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_FORWARD_CMD){
        players.jumpForwardWorm();
    }
}

void Model::leftWorm() {
    players.leftWorm();
}

void Model::rightWorm() {
    players.rightWorm();
}

void Model::jumpBackWorm() {
    players.jumpBackWorm();
}

void Model::updateStateWorms() {
    players.updateStateWorms();
}

std::vector<WeaponsDTO> Model::getVecWeaponsDTO() const {
    return players.getVecWeaponsDTO();
}





