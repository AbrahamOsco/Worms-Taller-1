//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_TELEPORT_H
#define WORMS_TALLER_1_TELEPORT_H


#include "Weapon.h"
#include "box2d/box2d.h"

class Teleport : public Weapon {
private:

public:
    Teleport(const TypeWeapon& aTypeWeapon, const float &damagePrincipal, const TypeMunition& aTypeMunition, const size_t& aMunition, const GameParameters& gameParameters);

    void teleportIn(b2Body *bodyWorm, const float &posXTeleport, const float &posYTeleport);

    virtual bool hasAScope() override;

};


#endif //WORMS_TALLER_1_TELEPORT_H
