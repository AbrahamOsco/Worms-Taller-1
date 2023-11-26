//
// Created by abraham on 20/11/23.
//

#include <iostream>
#include <algorithm>
#include "Explodable.h"
#include "../../QueriesToWorld/SaveWormsInAreaQuery.h"
#include "../../Worm/Worm.h"

Explodable::Explodable(const float &mainDamage, const float &maxRadio, const float &maxImpulseMagnitude) :
    mainDamage(mainDamage), maxRadio(maxRadio), maxImpulseMagnitude(maxImpulseMagnitude) {
}

b2AABB Explodable::getAreaForSearch(const b2Vec2 &positionProjectile) const {
    b2AABB searchArea;
    searchArea.lowerBound = positionProjectile - b2Vec2(maxRadio, maxRadio);
    searchArea.upperBound = positionProjectile + b2Vec2(maxRadio, maxRadio);
    return searchArea;
}


b2Vec2 Explodable::getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                                     const float &distanceWormToProjectile) {
    b2Vec2 impulseDirection = positionWorm - positionProjectile;
    impulseDirection.Normalize();
    float impulseMagnitude = maxImpulseMagnitude * std::max(0.0f, 1.0f - sqrt(distanceWormToProjectile) / maxRadio);
    b2Vec2 impulseWorm = impulseMagnitude * impulseDirection;
    if (impulseDirection.x == 0) {  // Si la normal en x es cero hizo un tiro a -90º sale volando para arriba.
        impulseWorm.y = maxImpulseMagnitude;
    }
    return impulseWorm;
}

float Explodable::getDamageForWorm(const float &wormDistanceSquared) {
    return mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistanceSquared) / maxRadio);
}

void Explodable::searchWormAndCollide(const b2Vec2 &projectilePosition, b2World *aWorld) {
    SaveWormsInAreaQuery saveWormsinArea(projectilePosition);
    aWorld->QueryAABB(&saveWormsinArea, this->getAreaForSearch(projectilePosition) );
    for ( auto& aElement : saveWormsinArea.getWormsAndDistSquared() ) {
        Worm* aWormToTakeDamage = (Worm*)(aElement.first);
        b2Vec2 impulseForWorm = this->getImpulseForWorm(aWormToTakeDamage->getBody()->GetWorldCenter(),
            projectilePosition, aElement.second);
        float damageForWorm = this->getDamageForWorm(aElement.second);
        aWormToTakeDamage->getBody()->ApplyLinearImpulse(impulseForWorm,
            aWormToTakeDamage->getBody()->GetWorldCenter(), true);
        aWormToTakeDamage->takeDamage(damageForWorm);
    }
}


