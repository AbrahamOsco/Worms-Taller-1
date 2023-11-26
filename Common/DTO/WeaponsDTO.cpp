//
// Created by abraham on 09/11/23.
//

#include "WeaponsDTO.h"

WeaponsDTO::WeaponsDTO() : DTO(WEAPONS_TOTAL), idPlayer(0), weaponCurrent(BANANA) {
}

WeaponsDTO::WeaponsDTO(const size_t &idPlayer, const std::vector<WeaponDTO> &aWeapons, const TypeWeapon& weaponCurrent)
        : DTO(WEAPONS_TOTAL), idPlayer(idPlayer), weapons(aWeapons), weaponCurrent(weaponCurrent) {
}


std::vector<WeaponDTO> WeaponsDTO::getWeapons() const {
    return weapons;
}

void WeaponsDTO::setWeapons(const std::vector<WeaponDTO> &weapons) {
    this->weapons = weapons;
}

size_t WeaponsDTO::getIdPlayer() const {
    return idPlayer;
}

void WeaponsDTO::setIdPlayer(const size_t &idPlayer) {
    this->idPlayer = idPlayer;
}

TypeWeapon WeaponsDTO::getWeaponCurrent() const {
    return weaponCurrent;
}

void WeaponsDTO::setWeaponCurrent(const TypeWeapon &weaponCurrent) {
    this->weaponCurrent = weaponCurrent;
}

bool WeaponsDTO::operator==(const WeaponsDTO& other) const {
    return  this->opType == other.opType &&
            this->idPlayer == other.idPlayer &&
            this->weapons == other.weapons &&
            this->weaponCurrent == other.weaponCurrent;
}
