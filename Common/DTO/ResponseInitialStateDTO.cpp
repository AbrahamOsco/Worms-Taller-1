//
// Created by abraham on 26/10/23.
//

#include "ResponseInitialStateDTO.h"

ResponseInitialStateDTO::ResponseInitialStateDTO() :DTO(INITIAL_STATE) {

}

void ResponseInitialStateDTO::setGameName(const std::string &aGameName) {
    this->gameName = aGameName;
}

void ResponseInitialStateDTO::setScenarioName(const std::string &aScenarioName) {
    this->scenarioName = aScenarioName;
}

void ResponseInitialStateDTO::setPlayerRequired(const size_t &aPlayersRequired) {
    this->playersRequired = aPlayersRequired;
}

std::string ResponseInitialStateDTO::getGameName() const {
    return gameName;
}

std::string ResponseInitialStateDTO::getScenarioName() const {
    return scenarioName;
}

size_t ResponseInitialStateDTO::getPlayerRequired() const {
    return playersRequired;
}

