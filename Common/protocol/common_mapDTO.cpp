#include "common_mapDTO.h"

MapDTO::MapDTO(const std::vector<BeamDTO> &beams) : opType(MAP), beams(beams) {}

int MapDTO::getOpType() {
    return opType;
}

unsigned int MapDTO::getNumBeams() {
    return beams.size();
}

std::vector<BeamDTO> &MapDTO::getBeams() {
    return beams;
}
