//
// Created by abraham on 20/11/23.
//

#ifndef WORMS_TALLER_1_AIRATTACKMISSILE_H
#define WORMS_TALLER_1_AIRATTACKMISSILE_H


#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"
#include "../../../GameParameters/GameParameters.h"
#include "../../../../Common/DTO/DTO.h"
#include "../../../../Common/DTO/ProjectileDTO.h"

class AirAttackMissile : public GameObject {
private:
    float mainDamage ;
    float maxRadio;
    float maxImpulseMagnitude;
    const GameParameters& gameParameters;
    b2World* aWorld;
    TypeFocus typeFocus;
public:

    AirAttackMissile(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void addToTheWorld(b2World *aWorld, const b2Vec2 &positionMissile, const float &windValue);

    ProjectileDTO getProjectilDTO();

    // pasar a una clase y delegarlo.

    b2AABB getAreaForSearch(const b2Vec2 &positionMissile) const;

    b2Vec2
    getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                      const float &distanceWormToProjectile);

    float getDamageForWorm(const float &wormDistanceSquared);

    b2World *getWorld();
};


#endif //WORMS_TALLER_1_AIRATTACKMISSILE_H
