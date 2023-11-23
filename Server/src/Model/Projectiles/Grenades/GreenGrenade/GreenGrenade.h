//
// Created by abraham on 22/11/23.
//

#ifndef WORMS_TALLER_1_GREENGRENADE_H
#define WORMS_TALLER_1_GREENGRENADE_H


#include "../Grenade/Grenade.h"
#include "../../Explodable/Explodable.h"

class GreenGrenade : public Grenade {
public:
    GreenGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    ~GreenGrenade() = default;
};


#endif //WORMS_TALLER_1_GREENGRENADE_H
