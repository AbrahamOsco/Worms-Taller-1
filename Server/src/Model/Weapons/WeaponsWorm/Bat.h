//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_BAT_H
#define WORMS_TALLER_1_BAT_H

#include <utility>
#include "Weapon.h"
#include "../WeaponRayCast/WeaponRayCast.h"
#include "../WeaponSight/WeaponSight.h"


// agregar weponaSight t toda la gracia.
class Bat : public Weapon{
 private:
    std::pair<float, float> impulseWeapon;
    WeaponSight weaponSight;

 public:
    Bat(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
        const size_t &aMunition, const GameParameters& gameParameters);

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) override;

    void increaseAngle() override;

    void decreaseAngle() override;

    bool hasAScope() override;

    bool hasVariablePower() override;

    bool launchesProjectiles() override;

    // virtual void prepareWeapon(const Direction &aDirection) override;
    void searchWormAndAttack(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent);
};


#endif  // WORMS_TALLER_1_BAT_H
