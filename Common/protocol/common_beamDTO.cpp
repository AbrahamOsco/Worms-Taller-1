#include "common_beamDTO.h"

BeamDTO::BeamDTO(int x, int y, int angle, BeamDTO::BeamType type) :
    opType(BEAM), x(x), y(y), angle(angle), type(type) {}

int BeamDTO::getOpType() {
    return opType;
}

int BeamDTO::getBeamType() {
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
