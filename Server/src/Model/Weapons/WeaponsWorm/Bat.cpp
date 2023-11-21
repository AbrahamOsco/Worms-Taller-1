//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Bat.h"
#include "../../Worm/Worm.h"

Bat::Bat(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
         const size_t &aMunition, const GameParameters& gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition, gameParameters),
         weaponSight(gameParameters.getBatRayLength(), gameParameters.getWeaponAngleInitial() , gameParameters){
    impulseWeapon = std::make_pair(gameParameters.getBatImpulseX(), gameParameters.getBatImpulseY());
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

void Bat::searchWormAndAttack(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent){
    GameObject* gameObject = weaponSight.getBodyCollidesWithRayCast(world, positionWorm, directionCurrent);
    if ( gameObject == nullptr){
        std::cout << "No se golpeo a ningun worm \n";         // signfica que no alcanza a nadie nuestro ataque o golpeamos a algo que no es un worm  por ej una viga
        return;
    }
    Worm* wormForAttack = (Worm*) gameObject;
    wormForAttack->takeDamage(getMainDamage());
    float factor = 1.0f;
    if(directionCurrent == LEFT){
        factor = -1.0f;
    }
    wormForAttack->getBody()->ApplyLinearImpulse(b2Vec2(factor * impulseWeapon.first, impulseWeapon.second), wormForAttack->getBody()->GetWorldCenter(), true);
    weaponSight.resetRayCast();
}

WeaponSightDTO Bat::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent){
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}

bool Bat::launchesProjectiles() {
    return false;
}

bool Bat::hasVariablePower() {
    return false;
}
