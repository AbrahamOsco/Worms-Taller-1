//
// Created by abraham on 22/11/23.
//

#ifndef WORMS_TALLER_1_GRENADE_H
#define WORMS_TALLER_1_GRENADE_H


#include <chrono>
#include "../../WeaponSight/WeaponSight.h"
#include "../../../Projectiles/Explodable/Explodable.h"

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
    WeaponSight weaponSight;
    Explodable explodable;

public:
    //explicit Grenade(const GameParameters &gameParameters, const TypeFocus& typeFocus, int timeWait);

    void addToTheWorld(b2World* aWorld, b2Vec2 positionOrigen, b2Vec2 impulseGrenade);

    void collide();

    void passTime();

    void explode();

    bool hasExploded() const;

    virtual void throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades);

    virtual ~Grenade() = default;
};


#endif //WORMS_TALLER_1_GRENADE_H
