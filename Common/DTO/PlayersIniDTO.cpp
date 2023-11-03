//
// Created by abraham on 02/11/23.
//

#include "PlayersIniDTO.h"

PlayersIniDTO::PlayersIniDTO() : DTO(PLAYERS_INITIAL) {
}


PlayersIniDTO::PlayersIniDTO(const std::vector<PlayerDTO> &aPlayersDTO) : DTO(PLAYERS_INITIAL), playersDTO(aPlayersDTO) {

}

std::vector<PlayerDTO> PlayersIniDTO::getPlayersIniDTO() const {
    return this->playersDTO;
}

void PlayersIniDTO::setPlayersIniDTO(const std::vector<PlayerDTO> &aPlayersDTO) {
    this->playersDTO = aPlayersDTO;
}


