//
// Created by abraham on 26/10/23.
//

#include "ResponseInitialStateDTO.h"

ResponseInitialStateDTO::ResponseInitialStateDTO() :DTO(INITIAL_STATE) {
}

ResponseInitialStateDTO::ResponseInitialStateDTO(const OperationType &aOperationType, const std::string &aGameName) : DTO(aOperationType), gameName(aGameName)  {
}

ResponseInitialStateDTO::ResponseInitialStateDTO(const OperationType &aOperationType, const std::string &aGameName,
                                                 const std::string &aScenarioName, const size_t &playersRequired)
                                                : DTO(aOperationType), gameName(aGameName), scenarioName(aScenarioName), playersRequired(playersRequired)  {

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


