//
// Created by abraham on 26/10/23.
//

#include "RoomDTO.h"


RoomDTO::RoomDTO() : DTO(ROOM_GAME), playersCurrent(0), playersRequired(0) {
}

RoomDTO::RoomDTO(const std::string &aGameName, const std::string &aScenarioName, const size_t &aPlayerCurrent,
                 const size_t &aPlayersRequired) : DTO(ROOM_GAME), gameName(aGameName) , scenarioName(aScenarioName),
                 playersCurrent(aPlayerCurrent), playersRequired(aPlayersRequired) {}




void RoomDTO::setGameName(const std::string &aGameName) {
    this->gameName = aGameName;
}

void RoomDTO::setScenarioName(const std::string &aScenarioName) {
    this->scenarioName = aScenarioName;
}

void RoomDTO::setPlayerRequired(const size_t &aPlayersRequired) {
    this->playersRequired = aPlayersRequired;
}

void RoomDTO::setPlayerCurent(const size_t &aPlayerCurrent) {
    this->playersCurrent = aPlayerCurrent;
}

std::string RoomDTO::getGameName() const {
    return gameName;
}

std::string RoomDTO::getScenarioName() const {
    return scenarioName;
}

size_t RoomDTO::getPlayerRequired() const {
    return playersRequired;
}

size_t RoomDTO::getPlayerCurrent() const {
    return playersCurrent;
}

