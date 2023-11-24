//
// Created by abraham on 29/10/23.
//

#include "StageDTO.h"

StageDTO::StageDTO() : DTO(STAGE) {}

StageDTO::StageDTO(const std::vector<BeamDTO> &beams, const size_t& positionYWater, const std::string& background) : DTO(STAGE),
            beams(beams), positionYWater(positionYWater), background(background) {}

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

bool StageDTO::operator==(const StageDTO& other) const {
    return  this->opType == other.opType  &&
            this->beams == other.beams  &&
            this->idPlayer == other.idPlayer;
}

size_t StageDTO::getPositionYWater() const {
    return positionYWater;
}

std::string StageDTO::getBackground() const {
    return background;
}

void StageDTO::setPositionYWater(const size_t &positionYWater) {
    this->positionYWater = positionYWater;
}

void StageDTO::setBackground(const std::string &background) {
    this->background = background;
}

