#include "BeamDTO.h"

BeamDTO::BeamDTO(int x, int y, int angle, BeamType type) :
        DTO(BEAM), x(x), y(y), angle(angle), type(type) {}


BeamType BeamDTO::getBeamType() const {
    return type;
}

int BeamDTO::getX() const {
    return x;
}

int BeamDTO::getY() const {
    return y;
}

int BeamDTO::getAngle() const {
    return angle;
}

BeamDTO::~BeamDTO() = default;
