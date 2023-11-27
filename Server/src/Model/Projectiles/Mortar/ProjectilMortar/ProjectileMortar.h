//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILEMORTAR_H
#define WORMS_TALLER_1_PROJECTILEMORTAR_H



#include "../../../GameObject/GameObject.h"
#include "../../../../../GameParameters/GameParameters.h"
#include "../../../../../../Common/DTO/DTO.h"
#include "../../Explodable/Explodable.h"
#include "../../../../../../Common/DTO/ProjectileDTO.h"
#include "box2d/box2d.h"

class ProjectileMortar : public GameObject {
 protected:
    const GameParameters& gameParameters;
    b2World* aWorld;
    TypeFocus typeFocus;
    Explodable explodable;
    int explosionIterations;
    float windValue;

 public:
    ProjectileMortar(const GameParameters &gameParameters, const TypeFocus &typeFocus);

    void addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile, const float &windValue);

    virtual void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO);

    virtual void searchWormAndCollide(const b2Vec2 &projectilePosition);

    virtual void throwFragments();

    bool hasExplosionIterations() const;

    void removeAIteration();

    int getNumberIterations() const;
<<<<<<< HEAD:Server/src/Model/Projectiles/Mortar/ProjectileMortar.h
=======

    virtual ~ ProjectileMortar() = default;

>>>>>>> ddca367 (Refactor del server se hacen las correciones):Server/src/Model/Projectiles/Mortar/ProjectilMortar/ProjectileMortar.h
};


#endif  // WORMS_TALLER_1_PROJECTILEMORTAR_H
