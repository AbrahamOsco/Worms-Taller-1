//
// Created by abraham on 09/11/23.
//

#include "WeaponDTO.h"
WeaponDTO::WeaponDTO() : DTO(WEAPON), typeWeapon(NONE_WEAPON) {
}

WeaponDTO::WeaponDTO(const TypeWeapon &aTypeWeapon, const TypeMunition &aTypeMunition, const size_t &aMunition)
        : DTO(WEAPON), typeWeapon(aTypeWeapon), typeMunition(aTypeMunition), munition(aMunition) {
}

TypeWeapon WeaponDTO::getTypeWeapon() const {
    return typeWeapon;
}

size_t WeaponDTO::getMunition() const {
    return munition;
}

void WeaponDTO::setTypeWeapon(const TypeWeapon &typeWeapon) {
    this->typeWeapon = typeWeapon;
}

void WeaponDTO::setMunition(const size_t &munition) {
    this->munition = munition;
}

TypeMunition WeaponDTO::getTypeMunition() const {
    return typeMunition;
}

void WeaponDTO::setATypeMunition(const TypeMunition &aTypeMunition) {
    this->typeMunition = aTypeMunition;
}

bool WeaponDTO::getIsSelected() const{
    return false;
}


