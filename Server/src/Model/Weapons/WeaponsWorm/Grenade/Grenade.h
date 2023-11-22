//
// Created by abraham on 22/11/23.
//

#ifndef WORMS_TALLER_1_GRENADE_H
#define WORMS_TALLER_1_GRENADE_H


#include <chrono>
#include "../../../../../GameParameters/GameParameters.h"
#include "../../WeaponSight/WeaponSight.h"

class Grenade {
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

public:
    explicit Grenade(GameParameters gameParameters);


};


#endif //WORMS_TALLER_1_GRENADE_H
