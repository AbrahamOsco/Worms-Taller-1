//
// Created by abraham on 29/10/23.
//

#include "StageDTO.h"

StageDTO::StageDTO() : DTO(STAGE) {}

StageDTO::StageDTO(const std::vector<BeamDTO> &beams) : DTO(STAGE), beams(beams) {}

void StageDTO::setBeams(const std::vector<BeamDTO> &beams) {
    this->beams = beams;
}

std::vector<BeamDTO> StageDTO::getBeams() const {
    return beams;
}

size_t StageDTO::getIdPlayer() const {
    return idPlayer;
}

void StageDTO::setIdPlayer(const size_t &idPlayer) {
    this->idPlayer = idPlayer;
}



