//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include "../../../Common/DTO/WormDTO.h"

#define LIFE_BONUS 25

class Worm {
    size_t idWorm;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY);

    void assignBonusLife();

    WormDTO getWormInitialDTO() const;
};


#endif //WORMS_TALLER_1_WORM_H
