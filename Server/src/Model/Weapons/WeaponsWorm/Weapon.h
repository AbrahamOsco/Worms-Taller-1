//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPON_H
#define WORMS_TALLER_1_WEAPON_H

#include <vector>
#include "../../../../../Common/DTO/WeaponDTO.h"
#include "../../../../../Common/DTO/WormDTO.h"
#include "../../../../GameParameters/GameParameters.h"
#include "box2d/b2_math.h"
#include "../../../../../Common/DTO/WeaponSightDTO.h"
#include "../../../../../Common/DTO/ProjectileDTO.h"
#include "box2d/b2_world.h"

#define DEGRATORADIANS (b2_pi/180.0f)

class Weapon {
 protected:
    TypeWeapon typeWeapon;
    float mainDamage;
    TypeMunition typeMunition;
    size_t munition;
    const GameParameters& gameParameters;
    float windValue;

 public:
    explicit Weapon(const TypeWeapon& aTypeWeapon, const float &mainDamage, const TypeMunition& aTypeMunition,
                    const size_t& aMunition, const GameParameters& gameParameters);

    WeaponDTO getWeaponDTO() const;

    float getMainDamage() const;

    virtual bool hasVariablePower() = 0;

    virtual bool launchesProjectiles() = 0;

    // Estos 3 para toda arma que lanza proyectiles.

    virtual bool thereAreProjectiles();

    virtual void tryCleanProjectiles(b2World* aWorld);

    virtual void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO);


    // estos 2 metodos armas con potencia variable.

    virtual bool increaseImpulse();

    virtual bool hasAScope();

    // metodods para la mira estos 3
    virtual void increaseAngle();

    virtual void decreaseAngle();

    virtual WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent);

    // para todas las armas con cuenta regresiva;
    virtual void passTime();

    // para las armas con municioness:
    virtual bool hasMunition() const;

    void assignWindValue(const float &aWindValue);

    void giveExtraMunition(const size_t &extraMunition);

    virtual ~Weapon() = default;
};


#endif  // WORMS_TALLER_1_WEAPON_H
