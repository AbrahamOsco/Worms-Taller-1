//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_MORTARMAINPROJECTILE_H
#define WORMS_TALLER_1_MORTARMAINPROJECTILE_H

#include "../ProjectileMortar.h"

class MortarMainProjectile : public ProjectileMortar {
private:
    std::vector<b2Vec2> fragmentImpulses;
    std::vector<std::unique_ptr<ProjectileMortar>> fragments;
public:
    MortarMainProjectile(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    void throwFragments() override;

    bool hasFragment() const;

    void tryCleanProjectiles();

    void getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO);
};


#endif //WORMS_TALLER_1_MORTARMAINPROJECTILE_H
