//
// Created by abraham on 25/10/23.
//

#include "InitialStateDTO.h"

InitialStateDTO::InitialStateDTO() : DTO(INITIAL_STATE) {

}

void InitialStateDTO::setPlayerName(const std::string &aPlayerName) {
    this->playerName = aPlayerName;
}

std::string InitialStateDTO::getPlayerName() const {
    return this->playerName;
}



