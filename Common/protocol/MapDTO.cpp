#include "MapDTO.h"

MapDTO::MapDTO(const std::vector<BeamDTO> &beams) : DTO(MAP), beams(beams) {}

unsigned int MapDTO::getNumBeams() {
    return beams.size();
}

std::vector<BeamDTO> &MapDTO::getBeams() {
    return beams;
}

MapDTO::~MapDTO() = default;
