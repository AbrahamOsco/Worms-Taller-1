#include "common_wormDTO.h"

WormDTO::WormDTO(int x, int y) : opType(WORM), x(x), y(y) {}

int WormDTO::getOpType() {
    return opType;
}

int WormDTO::getX() const {
    return x;
}

int WormDTO::getY() const {
    return y;
}
