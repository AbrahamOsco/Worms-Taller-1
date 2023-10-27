//
// Created by abraham on 26/10/23.
//

#include "ResolverInitialDTO.h"

ResolverInitialDTO::ResolverInitialDTO() : DTO(INITIAL_STATE) {

}

ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType,
                                       const std::vector<std::string> &aScenariosNames) : DTO(operationType), scenariosNames(aScenariosNames) {
}

ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType, const std::vector<RoomDTO> &aGameRooms) : DTO(operationType), gameRooms(aGameRooms) {

}
ResolverInitialDTO::ResolverInitialDTO(const OperationType &operationType, const size_t &aStatusAnswer) : DTO(operationType), statusAnswer(aStatusAnswer) {

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

