//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include "Worm.h"

Worm::Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : positionInitialX(posIniX), positionInitialY(posIniY) {
    this->idWorm = idWorm;
    hp = 100.0f;
    dragSpeed = 1.2f;
}

void Worm::assignBonusLife() {
    hp += LIFE_BONUS;
}

WormDTO Worm::getWormInitialDTO() const {
    return WormDTO(idWorm, positionInitialX, positionInitialY);
}



