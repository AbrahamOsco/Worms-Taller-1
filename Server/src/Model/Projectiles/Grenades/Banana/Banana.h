//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_BANANA_H
#define WORMS_TALLER_1_BANANA_H


#include "../Grenade/Grenade.h"
#include "../../Explodable/Explodable.h"

class Banana : public Grenade {
private:
public:

    Banana(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    ~Banana() = default;
};


#endif //WORMS_TALLER_1_BANANA_H
