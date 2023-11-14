//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Bat.h"

Bat::Bat(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
         const size_t &aMunition, const GameParameters& gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition, gameParameters),
         weaponSight(gameParameters.getBatRayLength(), gameParameters.getWeaponAngleInitial() , gameParameters){
    impulseWeapon = std::make_pair(gameParameters.getBatImpulseX(), gameParameters.getBatImpulseY());
}

float Bat::getImpulseX() const {
    return impulseWeapon.first;
}

float Bat::getImpulseY() const {
    return impulseWeapon.second;
}

void Bat::increaseAngle() {
    weaponSight.increaseAngle();
}
void Bat::decreaseAngle() {
    weaponSight.decreaseAngle();
}


bool Bat::hasAScope(){
    return true;
}

void Bat::resetRayCast(){
    this->weaponSight.resetRayCast();
}

GameObject *Bat::getBodyCollidesWithRayCast(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getBodyCollidesWithRayCast(world, positionWorm, directionCurrent);
}

WeaponSightDTO Bat::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent){
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}