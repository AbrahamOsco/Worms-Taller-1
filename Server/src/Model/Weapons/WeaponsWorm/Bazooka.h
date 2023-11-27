//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_BAZOOKA_H
#define WORMS_TALLER_1_BAZOOKA_H

#include <memory>
#include <utility>
#include <vector>
#include "Weapon.h"
#include "../WeaponSight/WeaponSight.h"
#include "../../Projectiles/ProjectileBazooka.h"

class Bazooka : public Weapon {
 private:
    std::pair<float, float> impulseWeapon;  // impulse x, impulse y
    WeaponSight weaponSight;
    std::unique_ptr<ProjectileBazooka> projectil;
    std::pair<float, float> maxImpulseWeapon;
    int explosionIterations;

 public:
    explicit Bazooka(const TypeWeapon& aTypeWeapon, const float &damagePrincipal, const TypeMunition& aTypeMunition,
                    const size_t& aMunition, const GameParameters& gameParameters);

    void increaseAngle() override;

    void decreaseAngle() override;

    bool hasAScope() override;

    bool hasVariablePower() override;

    bool increaseImpulse() override;

    bool launchesProjectiles() override;

    bool thereAreProjectiles() override;

    void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    void tryCleanProjectiles(b2World* aWorld) override;

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) override;

    void shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction,
            const TypeFocus &focus);
};


#endif  // WORMS_TALLER_1_BAZOOKA_H
