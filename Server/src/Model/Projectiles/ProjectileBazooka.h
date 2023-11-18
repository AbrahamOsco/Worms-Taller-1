//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILEBAZOOKA_H
#define WORMS_TALLER_1_PROJECTILEBAZOOKA_H


#include "../../../GameParameters/GameParameters.h"
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"

class ProjectileBazooka : public GameObject {
private:

    float mainDamage;
    float radio;
    float maxImpulseExplosion;
    const GameParameters& gameParameters;
    b2World* aWorld;
public:

    explicit ProjectileBazooka(const GameParameters &gameParameters);

    b2AABB getAreaForSearch(const b2Vec2& positionMunition) const;

    void addToTheWorld(b2World* aWorld, b2Vec2 positionP2, const b2Vec2& impulseProjectile);

    b2Vec2 getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile, const float &distanceWormToProjectile);

    float getDamageForWorm(const float &wormDistanceSquared);


    b2World *getWorld();
};


#endif //WORMS_TALLER_1_PROJECTILEBAZOOKA_H
