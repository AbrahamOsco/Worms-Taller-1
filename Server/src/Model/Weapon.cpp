//
// Created by abraham on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
               const size_t &aMunition, const GameParameters &gameParameters) : typeWeapon(aTypeWeapon), damagePrincipal(damagePrincipal),
               typeMunition(aTypeMunition), munition(aMunition), gameParameters(gameParameters) {
}

TypeWeapon Weapon::getTypeWeapon() const {
    return typeWeapon;
}

float Weapon::getMainDamage() const {
    return damagePrincipal;
}

TypeMunition Weapon::getTypeMunition() const {
    return typeMunition;
}

size_t Weapon::getMunition() const {
    return munition;
}


void Weapon::increaseAngle() {
    // no hago nada caso de dinamita- teleport y air attack
}

void Weapon::decreaseAngle() {
    // no hago nada caso de dinamita- teleport y air attack
}

/*
void Weapon::prepareWeapon(const Direction &aDirection) {
    // no hago nada caso de dinamita -telepor y air attack.
}
*/


WeaponDTO Weapon::getWeaponDTO() const {
    return WeaponDTO(typeWeapon, typeMunition, munition);
}

WeaponSightDTO Weapon::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
}



