//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPON_H
#define WORMS_TALLER_1_WEAPON_H


#include "../../../Common/DTO/WeaponDTO.h"
#include "../../../Common/DTO/WormDTO.h"

class Weapon {
public:
    TypeWeapon typeWeapon;
    float damagePrincipal;
    TypeMunition typeMunition;
    size_t munition;

public:
    explicit Weapon(const TypeWeapon& aTypeWeapon, const float &damagePrincipal, const TypeMunition& aTypeMunition, const size_t& aMunition);

    TypeWeapon getTypeWeapon() const;

    float getMainDamage() const;

    TypeMunition getTypeMunition() const;

    size_t getMunition() const;

    virtual bool hasAScope() = 0;

    virtual void riseAngle();

    virtual void lowerAngle();

    virtual void changeDirection(const Direction &aDirection);

    virtual void prepareWeapon(const Direction& aDirection);

};


#endif //WORMS_TALLER_1_WEAPON_H
