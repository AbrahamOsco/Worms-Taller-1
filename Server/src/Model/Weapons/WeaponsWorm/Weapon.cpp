//
// Created by abraham on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
               const size_t &aMunition, const GameParameters &gameParameters) : typeWeapon(aTypeWeapon),
               mainDamage(mainDamage), typeMunition(aTypeMunition), munition(aMunition),
               gameParameters(gameParameters), windValue(0) {
}


float Weapon::getMainDamage() const {
    return mainDamage;
}


void Weapon::increaseAngle() {
    // no hago nada caso de dinamita- teleport y air attack
}

void Weapon::decreaseAngle() {
    // no hago nada caso de dinamita- teleport y air attack
}

WeaponDTO Weapon::getWeaponDTO() const {
    return WeaponDTO(typeWeapon, typeMunition, munition);
}

WeaponSightDTO Weapon::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
}

bool Weapon::increaseImpulse() {
    return false;
    // devuelvo false nunca llega al maximo porque no tiene /  no hago nada para algunas armas y las armas sin mira.
}

void Weapon::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    // no hago nada para las armas sin mira y armas q no lanzan projectiles
}

void Weapon::tryCleanProjectiles(b2World *aWorld) {
    // no hago nada para las armas que ni lanzan projectiles ni las armas sin mira
}

// no respondo nada util segun el arma en standabye que tengo respondo
bool Weapon::thereAreProjectiles() {
    return false;
}

void Weapon::assignWindValue(const float &aWindValue) {
    this->windValue = aWindValue;
}

void Weapon::giveExtraMunition(const size_t &extraMunition) {
    if (munition + extraMunition <= gameParameters.getMaxMunitionWeapon()) {
        munition +=extraMunition;
    }
}

void Weapon::passTime() {
}


bool Weapon::hasMunition() const {
    return true;
}

bool Weapon::hasAScope() {
    return false;
}
