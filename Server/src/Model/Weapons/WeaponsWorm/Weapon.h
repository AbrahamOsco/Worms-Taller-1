//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPON_H
#define WORMS_TALLER_1_WEAPON_H


#include "../../../../../Common/DTO/WeaponDTO.h"
#include "../../../../../Common/DTO/WormDTO.h"
#include "../../../../GameParameters/GameParameters.h"
#include "box2d/b2_math.h"
#include "../../../../../Common/DTO/WeaponSightDTO.h"
#include "../../../../../Common/DTO/ProjectileDTO.h"

#define DEGRATORADIANS (b2_pi/180.0f)
#define RADIANSTODEGREE (180/b2_pi)

class Weapon {
public:
    TypeWeapon typeWeapon;
    float mainDamage;
    TypeMunition typeMunition;
    size_t munition;
    const GameParameters& gameParameters;

public:
    explicit Weapon(const TypeWeapon& aTypeWeapon, const float &mainDamage, const TypeMunition& aTypeMunition,
                    const size_t& aMunition, const GameParameters& gameParameters);

    TypeWeapon getTypeWeapon() const;

    WeaponDTO getWeaponDTO() const;

    float getMainDamage() const;

    TypeMunition getTypeMunition() const;

    size_t getMunition() const;

    virtual bool hasAScope() = 0;

    virtual bool launchesProjectiles() = 0;

    // metodods para la mira

    virtual void increaseAngle();

    virtual void decreaseAngle();

    virtual void  increaseImpulse();

    virtual bool hasMaxImpulse();

    virtual void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO);

    virtual WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent);

};


#endif //WORMS_TALLER_1_WEAPON_H
