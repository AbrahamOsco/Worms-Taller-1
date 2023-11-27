//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_MORTARMAINPROJECTILE_H
#define WORMS_TALLER_1_MORTARMAINPROJECTILE_H

<<<<<<< HEAD
#include <memory>
#include <vector>
#include "../ProjectileMortar.h"
=======
#include "../ProjectilMortar/ProjectileMortar.h"
>>>>>>> ddca367 (Refactor del server se hacen las correciones)

class MortarMainProjectile : public ProjectileMortar {
 private:
    std::vector<b2Vec2> fragmentImpulses;
    std::vector<std::unique_ptr<ProjectileMortar>> fragments;
    bool wasThrowFragments;
 public:
    MortarMainProjectile(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    void throwFragments() override;

    void searchWormAndCollide(const b2Vec2 &projectilePosition) override;

    bool hasFragment() const;

    void tryCleanProjectiles();

    void getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO);

    void awakenFragments();
};


#endif  // WORMS_TALLER_1_MORTARMAINPROJECTILE_H
