//
// Created by abraham on 26/10/23.
//

#include "ResolverInitialDTO.h"

ResolverInitialDTO::ResolverInitialDTO() : DTO(INITIAL_STATE),  statusAnswer(0) {
}

ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType,
                    const std::vector<std::string> &aScenariosNames, const std::vector<size_t>& vecMaxNumbersWorms) :
                    DTO(operationType), scenariosNames(aScenariosNames), vecMaxNumbersWorms(vecMaxNumbersWorms),
                    statusAnswer(0) {
}

ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType,
const std::vector<RoomDTO> &aGameRooms) : DTO(operationType), gameRooms(aGameRooms), statusAnswer(0)  {
}
ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType, const size_t &aStatusAnswer) :
DTO(operationType), statusAnswer(aStatusAnswer) {
}

void ResolverInitialDTO::setScenarioNames(const std::vector<std::string> &aScenariosNames) {
    this->scenariosNames = aScenariosNames;
}

void ResolverInitialDTO::setStatusAnswer(const size_t &aStatusAnswer) {
    this->statusAnswer = aStatusAnswer;
}

void ResolverInitialDTO::setGameRooms(const std::vector<RoomDTO> &aGameRooms) {
    this->gameRooms = aGameRooms;
}

std::vector<std::string> ResolverInitialDTO::getScenariosNames() const {
    return scenariosNames;
}

size_t ResolverInitialDTO::getStatusAnswer() const {
    return statusAnswer;
}

std::vector<RoomDTO> ResolverInitialDTO::getGameRooms() const {
    return gameRooms;
}

std::vector<size_t> ResolverInitialDTO::getVecMaxNumbersWorms() const {
    return vecMaxNumbersWorms;
}

void ResolverInitialDTO::setVecMaxNumbersWorms(const std::vector<size_t> &vecMaxNumbersWorms) {
    this->vecMaxNumbersWorms = vecMaxNumbersWorms;
}

bool ResolverInitialDTO::operator==(const ResolverInitialDTO& other) const {
    return  this->opType == other.opType &&
            this->scenariosNames == other.scenariosNames &&
            this->vecMaxNumbersWorms == other.vecMaxNumbersWorms &&
            this->statusAnswer == other.statusAnswer &&
            this->gameRooms == other.gameRooms;
}
