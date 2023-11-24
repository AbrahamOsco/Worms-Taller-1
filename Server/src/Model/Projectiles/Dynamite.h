//
// Created by abraham on 21/11/23.
//

#ifndef WORMS_TALLER_1_DYNAMITE_H
#define WORMS_TALLER_1_DYNAMITE_H


#include <chrono>
#include "box2d/box2d.h"
#include "Explodable/Explodable.h"
#include "../GameObject/GameObject.h"
#include "../../../../Common/DTO/ProjectileDTO.h"
#include "../../../GameParameters/GameParameters.h"

class Dynamite : public GameObject {
private:
    std::chrono::steady_clock::time_point startTime, time;
    std::chrono::duration<float> waitTime;
    bool exploded;
    b2World *world;
    GameParameters gameParameters;
    Explodable explodable;
    TypeFocus typeFocus;
public:
    explicit Dynamite(const int &waitTime, const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void addToTheWorld(b2World* aWorld, b2Vec2 position);

    // para la dynamite
    void passTime();

    void explode();

    bool hasExploded() const;

    // necesarios
    void searchWormAndCollide(const b2Vec2 &projectilePosition);

    ProjectileDTO getProjectilDTO();

};


#endif //WORMS_TALLER_1_DYNAMITE_H
