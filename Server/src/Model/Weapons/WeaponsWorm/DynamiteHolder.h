//
// Created by abraham on 21/11/23.
//

#ifndef WORMS_TALLER_1_DYNAMITEHOLDER_H
#define WORMS_TALLER_1_DYNAMITEHOLDER_H


#include "Weapon.h"
#include "../../Projectiles/Dynamite.h"

class DynamiteHolder : public Weapon {
private:
    std::unique_ptr<Dynamite> dynamite;
public:
    DynamiteHolder(const TypeWeapon &aTypeWeapon, const float &mainDamage,
                   const TypeMunition &aTypeMunition, const size_t &aMunition,
                   const GameParameters &gameParameters);

    void placeDynamite(const int &waitTime, const b2Vec2 &positionWorm, const Direction &aDirectionWorm, b2World *world,
                       const TypeFocus &typeFocus);

    bool hasAScope() override;

    bool hasVariablePower() override;

    bool launchesProjectiles() override;

    // Estos 3 para toda arma que lanza proyectiles.

    bool thereAreProjectiles() override;

    void tryCleanProjectiles(b2World* aWorld) override;

    void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

};


#endif //WORMS_TALLER_1_DYNAMITEHOLDER_H
