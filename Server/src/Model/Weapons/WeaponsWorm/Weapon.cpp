//
// Created by abraham on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
               const size_t &aMunition, const GameParameters &gameParameters) : typeWeapon(aTypeWeapon), mainDamage(mainDamage),
                                                                                typeMunition(aTypeMunition), munition(aMunition), gameParameters(gameParameters) {
}

TypeWeapon Weapon::getTypeWeapon() const {
    return typeWeapon;
}

float Weapon::getMainDamage() const {
    return mainDamage;
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
void Weapons::prepareWeapon(const Direction &aDirection) {
    // no hago nada caso de dinamita -telepor y air attack.
}
*/


WeaponDTO Weapon::getWeaponDTO() const {
    return WeaponDTO(typeWeapon, typeMunition, munition);
}

WeaponSightDTO Weapon::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
}

// devuelve true si llega al maximo falso si no.
bool Weapon::increaseImpulse() {
    return false; // devuelvo false nunca llega al maximo porque no tiene /  no hago nada para algunas armas y las armas sin mira.
}

bool Weapon::hasMaxImpulse() {
    return false;
}

void Weapon::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    // no hago nada para las armas sin mira y armas q no lanzan projectiles
}

void Weapon::tryCleanProjectiles(b2World *aWorld) {
 //no hago nada para las armas que ni lanzan projectiles ni las armas sin mira
}

// no respondo nada util segun el arma en standabye que tengo respondo
bool Weapon::thereAreProjectiles() {
    return false;
}

void Weapon::assignWindValue(const float &aWindValue) {
    this->windValue = aWindValue;
}


