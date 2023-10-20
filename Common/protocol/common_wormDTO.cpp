#include "common_wormDTO.h"

WormDTO::WormDTO(int x, int y) : DTO(WORM), x(x), y(y) {}

int WormDTO::getX() const {
    return x;
}

int WormDTO::getY() const {
    return y;
}

WormDTO::~WormDTO() = default;
