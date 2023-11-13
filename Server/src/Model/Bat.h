//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_BAT_H
#define WORMS_TALLER_1_BAT_H


#include "Weapon.h"
#include "WeaponRayCast.h"
#include "GameObject.h"
#define DEGRATORADIANS (b2_pi/180.0f)
#define RADIANSTODEGREE (180/b2_pi)

// agregar weponaSight t toda la gracia. 
class Bat : public Weapon{
private:
    float impulseX;
    float impulseY;
    float rayAngle;
    float rayLength;
    WeaponRayCast weaponRayCast;
    Direction direction;

public:
    Bat(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
        const size_t &aMunition);

    GameObject *getBodyShocked(b2World *world, const b2Vec2 &positionWorm);

    float getImpulseX() const;

    float getImpulseY() const;

    void resetRayCast();

    virtual void riseAngle() override;

    virtual void lowerAngle() override;

    virtual void changeDirection(const Direction &aDirection) override;

    virtual bool hasAScope() override;

    virtual void prepareWeapon(const Direction &aDirection) override;

};


#endif //WORMS_TALLER_1_BAT_H
