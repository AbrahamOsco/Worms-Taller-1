//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_BAT_H
#define WORMS_TALLER_1_BAT_H


#include "Weapon.h"
#include "WeaponRayCast.h"
#include "GameObject.h"
#include "WeaponSight.h"


// agregar weponaSight t toda la gracia. 
class Bat : public Weapon{
private:
    std::pair<float, float> impulseWeapon;
    WeaponSight weaponSight;
public:
    Bat(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
        const size_t &aMunition, const GameParameters& gameParameters);

    GameObject *getBodyCollidesWithRayCast(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent);

    float getImpulseX() const;

    float getImpulseY() const;

    void resetRayCast();

    virtual void increaseAngle() override;

    virtual void decreaseAngle() override;

    virtual bool hasAScope() override;

    //virtual void prepareWeapon(const Direction &aDirection) override;

    virtual WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) override;
};


#endif //WORMS_TALLER_1_BAT_H
