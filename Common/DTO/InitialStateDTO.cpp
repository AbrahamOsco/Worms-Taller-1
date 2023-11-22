//
// Created by abraham on 25/10/23.
//

#include "InitialStateDTO.h"

InitialStateDTO::InitialStateDTO() : DTO(INITIAL_STATE) {
}

InitialStateDTO::InitialStateDTO(const OperationType &operationType, const std::string &aPlayerName):
                DTO(operationType), playerName(aPlayerName) {
}

void InitialStateDTO::setPlayerName(const std::string &aPlayerName) {
    this->playerName = aPlayerName;
}

std::string InitialStateDTO::getPlayerName() const {
    return this->playerName;
}

bool InitialStateDTO::operator==(const InitialStateDTO& other) const {
    return *this == other &&
            this->playerName == other.playerName;
}

