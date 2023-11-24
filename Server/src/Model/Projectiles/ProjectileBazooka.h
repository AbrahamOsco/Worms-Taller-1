//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILEBAZOOKA_H
#define WORMS_TALLER_1_PROJECTILEBAZOOKA_H


#include "../../../GameParameters/GameParameters.h"
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"
#include "../../../../Common/DTO/DTO.h"
#include "../../../../Common/DTO/ProjectileDTO.h"
#include "Explodable/Explodable.h"

class ProjectileBazooka : public GameObject {
private:
    const GameParameters& gameParameters;
    b2World* aWorld;
    TypeFocus typeFocus;
    Explodable explodable;
public:

    explicit ProjectileBazooka(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile, const float &windValue);

    ProjectileDTO getProjectilDTO();

    virtual void searchWormAndCollide(const b2Vec2 &projectilePosition);
};


#endif //WORMS_TALLER_1_PROJECTILEBAZOOKA_H
