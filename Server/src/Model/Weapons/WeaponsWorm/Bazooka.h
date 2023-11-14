//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_BAZOOKA_H
#define WORMS_TALLER_1_BAZOOKA_H


#include "Weapon.h"
#include "../WeaponSight/WeaponSight.h"
#include "../../Projectiles/ProjectileBazooka.h"

class Bazooka : public Weapon {
private:
    std::pair<float, float> impulseWeapon; // impulse x, impulse y
    WeaponSight weaponSight;
    std::vector<std::unique_ptr<ProjectileBazooka>> projectiles;
    std::pair<float, float> maxImpulseWeapon;
public:
    explicit Bazooka(const TypeWeapon& aTypeWeapon, const float &damagePrincipal, const TypeMunition& aTypeMunition,
                    const size_t& aMunition, const GameParameters& gameParameters);

    void resetRayCast();

    virtual void increaseAngle() override;

    virtual void decreaseAngle() override;

    virtual bool hasAScope() override;

    virtual void increaseImpulse() override;

    void shootProjectile(b2World *world, const b2Vec2& positionWorm, const Direction& direction);

    std::vector<std::unique_ptr<ProjectileBazooka>> *getProjectiles();

};


#endif //WORMS_TALLER_1_BAZOOKA_H
