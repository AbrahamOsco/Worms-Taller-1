//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_FRAGMENTGRENADE_H
#define WORMS_TALLER_1_FRAGMENTGRENADE_H


#include "../Grenade/Grenade.h"

class FragmentGrenade : public Grenade {
private:

public:
    FragmentGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    ~FragmentGrenade() = default;
};


#endif //WORMS_TALLER_1_FRAGMENTGRENADE_H
