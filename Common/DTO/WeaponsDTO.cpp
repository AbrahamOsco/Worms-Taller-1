//
// Created by abraham on 09/11/23.
//

#include "WeaponsDTO.h"

WeaponsDTO::WeaponsDTO() : DTO(WEAPONS_TOTAL) {
}

WeaponsDTO::WeaponsDTO(const size_t &idPlayer, const std::vector<WeaponDTO> &aWeapons)
        : DTO(WEAPONS_TOTAL), idPlayer(idPlayer), weapons(aWeapons) {
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




