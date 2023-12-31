//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_TELEPORT_H
#define WORMS_TALLER_1_TELEPORT_H


#include "box2d/box2d.h"
#include "Weapon.h"
#define LIMIT_Y_TELEPORT 17.5


class Teleport : public Weapon {
 public:
    Teleport(const TypeWeapon& aTypeWeapon, const float &mainDamage, const TypeMunition& aTypeMunition,
        const size_t& aMunition, const GameParameters& gameParameters);

    void teleportIn(b2Body *bodyWorm, const int &posXPix, const int &posYPix, b2World *aWorld);

    bool hasAScope() override;

    bool hasVariablePower() override;

    bool launchesProjectiles() override;

    bool isPositionFree(const b2Vec2 &positionToTeleport, b2World *aWorld);
};


#endif  // WORMS_TALLER_1_TELEPORT_H
