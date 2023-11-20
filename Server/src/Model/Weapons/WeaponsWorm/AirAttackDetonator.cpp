//
// Created by abraham on 20/11/23.
//

#include "AirAttackDetonator.h"

AirAttackDetonator::AirAttackDetonator(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
                  const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition,gameParameters) {
    offsets = {-0.5f,0.5f,-1.5f,1.5f,-2.5f,2.5f};
}




