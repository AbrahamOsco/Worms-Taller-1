//
// Created by abraham on 02/11/23.
//

#include "PlayersDTO.h"

PlayersDTO::PlayersDTO() : DTO(PLAYERS_TOTAL) {
}


PlayersDTO::PlayersDTO(const std::vector<PlayerDTO> &aPlayersDTO) : DTO(PLAYERS_TOTAL), playersDTO(aPlayersDTO) {
}

std::vector<PlayerDTO> PlayersDTO::getPlayersDTO() const {
    return this->playersDTO;
}

void PlayersDTO::setPlayersIniDTO(const std::vector<PlayerDTO> &aPlayersDTO) {
    this->playersDTO = aPlayersDTO;
}

bool PlayersDTO::operator==(const PlayersDTO& other) const {
    return  this->opType == other.opType &&
            this->playersDTO == other.playersDTO;
}
