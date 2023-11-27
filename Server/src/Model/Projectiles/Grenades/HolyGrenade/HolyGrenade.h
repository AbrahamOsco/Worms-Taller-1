//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_HOLYGRENADE_H
#define WORMS_TALLER_1_HOLYGRENADE_H

#include <vector>
#include "../Grenade/Grenade.h"
#include "../../Explodable/Explodable.h"

class HolyGrenade : public Grenade {
 public:
    HolyGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    ~HolyGrenade() = default;
};


#endif  // WORMS_TALLER_1_HOLYGRENADE_H
