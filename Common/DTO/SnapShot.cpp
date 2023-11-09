//
// Created by abraham on 06/11/23.
//

#include "SnapShot.h"

SnapShot::SnapShot() : DTO(SNAP_SHOT) {

}

SnapShot::SnapShot(const std::vector<WormDTO> &wormsDTO, const PlayersDTO &aPlayersDTO) : DTO(SNAP_SHOT), wormsDTO(wormsDTO), playersDTO(aPlayersDTO)  {
}

void SnapShot::setWormsDTO(const std::vector<WormDTO> &wormsDTO) {
    this->wormsDTO = wormsDTO;
}

std::vector<WormDTO> SnapShot::getWormsDto() const {
    return wormsDTO;
}

PlayersDTO SnapShot::getPlayersDto() const {
    return playersDTO;
}

void SnapShot::setPlayersDto(const PlayersDTO &playersDto) {
    this->playersDTO = playersDto;
}



