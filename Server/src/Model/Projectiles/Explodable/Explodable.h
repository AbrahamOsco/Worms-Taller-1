//
// Created by abraham on 20/11/23.
//

#ifndef WORMS_TALLER_1_EXPLODABLE_H
#define WORMS_TALLER_1_EXPLODABLE_H


#include <box2d/b2_collision.h>
#include <box2d/b2_world.h>

class Explodable {
private:
    float mainDamage;
    float maxRadio;
    float maxImpulseMagnitude;

public:

    Explodable(const float& mainDamage, const float& maxRadio, const float& maxImpulseMagnitude);


    b2AABB getAreaForSearch(const b2Vec2 &positionProjectile) const;

    b2Vec2
    getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                      const float &distanceWormToProjectile);

    float getDamageForWorm(const float &wormDistanceSquared);

    void searchWormAndCollide(const b2Vec2 &projectilePosition, b2World *aWorld);
};


#endif //WORMS_TALLER_1_EXPLODABLE_H
