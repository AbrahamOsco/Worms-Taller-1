//
// Created by abraham on 09/11/23.
//

#include "WeaponsDTO.h"

WeaponsDTO::WeaponsDTO() : DTO(WEAPONS_TOTAL) {

}

WeaponsDTO::WeaponsDTO(const std::vector<WeaponDTO> &aWeapons) : DTO(WEAPONS_TOTAL), weapons(aWeapons){}

std::vector<WeaponDTO> WeaponsDTO::getWeapons() const {
    return weapons;
}

void WeaponsDTO::setWeapons(const std::vector<WeaponDTO> &weapons) {
    this->weapons = weapons;
}



