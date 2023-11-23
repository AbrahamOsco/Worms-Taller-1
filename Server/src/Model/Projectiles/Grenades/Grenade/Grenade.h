//
// Created by abraham on 22/11/23.
//

#ifndef WORMS_TALLER_1_GRENADE_H
#define WORMS_TALLER_1_GRENADE_H

#include <chrono>
#include "../../../GameObject/GameObject.h"
#include "../../../../../GameParameters/GameParameters.h"
#include "../../../Weapons/WeaponSight/WeaponSight.h"
#include "../../../../../../Common/DTO/ProjectileDTO.h"

class Grenade : public GameObject {
protected:
    std::pair<float, float> impulseWeapon; // impulse x, impulse y
    std::pair<float, float> maxImpulseWeapon;  // maximo impulso es una arma con potencia variable.
    float restitution;
    bool fixedRotation;
    std::chrono::steady_clock::time_point startTime, time;

    std::chrono::duration<float> waitTime;
    bool collided;
    bool exploded;
    GameParameters gameParameters;
    b2World *world;
    int explosionIterations;

public:
    explicit Grenade(GameParameters gameParameters, const int& waitTime);

    void addToTheWorld(b2World* aWorld, b2Vec2 positionOrigen, b2Vec2 impulseGrenade);

    void collide();

    bool hasExploded() const;

    virtual  void passTime() = 0;

    virtual void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades);

    virtual ProjectileDTO getProjectilDTO();

    bool hasExplosionIterations() const;

    void removeAIteration();

    int getNumberIterations() const;

    virtual ~Grenade() = default;

};


#endif //WORMS_TALLER_1_GRENADE_H
