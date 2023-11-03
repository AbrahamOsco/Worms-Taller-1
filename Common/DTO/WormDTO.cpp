#include "WormDTO.h"


WormDTO::WormDTO(const size_t &idWorm, const size_t &positionX, const size_t &positionY) : DTO(WORM) {

}

size_t WormDTO::getIdWorm() const {
    return idWorm;
}

size_t WormDTO::getPositionX() const {
    return positionX;
}

size_t WormDTO::getPositionY() const {
    return positionY;
}


WormDTO::~WormDTO() = default;

