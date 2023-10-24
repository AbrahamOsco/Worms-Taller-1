#include "MapDTO.h"

MapDTO::MapDTO(const std::vector<BeamDTO> &beams) : DTO(MAP), beams(beams) {}

unsigned int MapDTO::getNumBeams() const {
    return beams.size();
}

std::vector<BeamDTO> MapDTO::getBeams() const{
    return this->beams;
}

MapDTO::~MapDTO() = default;
