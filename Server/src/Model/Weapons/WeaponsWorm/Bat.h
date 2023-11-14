//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_BAT_H
#define WORMS_TALLER_1_BAT_H


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

    GameObject *getBodyCollidesWithRayCast(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent);

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) override;

    float getImpulseX() const;

    float getImpulseY() const;

    void resetRayCast();

    void increaseAngle() override;

    void decreaseAngle() override;

    bool hasAScope() override;

    bool launchesProjectiles() override;

    //virtual void prepareWeapon(const Direction &aDirection) override;
};


#endif //WORMS_TALLER_1_BAT_H
