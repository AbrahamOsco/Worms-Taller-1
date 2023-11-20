//
// Created by abraham on 20/11/23.
//

#ifndef WORMS_TALLER_1_AIRATTACKDETONATOR_H
#define WORMS_TALLER_1_AIRATTACKDETONATOR_H


#include "Weapon.h"
#include "../../Projectiles/AirAttackMissile.h"

class AirAttackDetonator : public Weapon {
private:
    std::vector<std::unique_ptr<AirAttackMissile>> missiles;
    std::vector<float> offsets;
    b2World* world;
public:
    AirAttackDetonator(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
                       const size_t &aMunition, const GameParameters &gameParameters);

    void detonate(const int& posXAttack, const int& posYAttack, b2World *world);


};


#endif //WORMS_TALLER_1_AIRATTACKDETONATOR_H
