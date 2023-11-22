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
#include "Explodable/Explodable.h"

class AirAttackMissile : public GameObject {
private:
    const GameParameters& gameParameters;
    b2World* aWorld;
    TypeFocus typeFocus;
    Explodable explodable;
    int explosionIterations;
public:

    AirAttackMissile(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void addToTheWorld(b2World *aWorld, const b2Vec2 &positionMissile, const float &windValue);

    ProjectileDTO getProjectilDTO();

    void searchWormAndCollide(const b2Vec2 &projectilePosition);

    bool hasExplosionIterations() const;

    void removeAIteration();

};


#endif //WORMS_TALLER_1_AIRATTACKMISSILE_H
