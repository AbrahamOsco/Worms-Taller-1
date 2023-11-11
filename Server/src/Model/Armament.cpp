//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Armament.h"
#include "Bat.h"
#include "Teleport.h"

Armament::Armament(const size_t &idPlayer) : idPlayer(idPlayer), currentWeapon(NONE_WEAPON), weaponOnStandBy(NONE_WEAPON) {
    armament.emplace(BASEBALL_BAT, std::make_unique<Bat>(BASEBALL_BAT, 10.0f, INFINITE, 1) );
    armament.emplace(TELEPORT, std::make_unique<Teleport>(TELEPORT, 0.0f, INFINITE, 1) );
}

bool Armament::isUnarmed() const{
    return this->currentWeapon == NONE_WEAPON;
}


TypeWeapon Armament::getWeaponCurrent() const {
    return this->currentWeapon;
}

void Armament::assignWeapon(const TypeWeapon &weapon, const Direction &direction) {
    this->currentWeapon = weapon;
    if (armament.at(currentWeapon)->hasAScope()){
        armament.at(currentWeapon)->prepareWeapon(direction);
    }
}

Weapon * Armament::getWeaponCurrentPtr() {
   // this->currentWeapon = aTypeWeapon; ->  SE LLAMA a asingWeapon antes de todo. el metodo de arriba.
    return armament.at(currentWeapon).get();
}

bool Armament::hasAScoped() {
    if(this->currentWeapon == NONE_WEAPON){
        std::cerr << "Error: [hasAScoped] estas intentado acceder a un arma pero la arma actual es NONE_WEAPN \n";
    }
    return this->armament.at(currentWeapon)->hasAScope();
}

void Armament::changeDirection(const Direction &direction) {
    if(this->currentWeapon == NONE_WEAPON){
        // en el caso de que estamos desarmado no hacemos nada.
        std::cerr << "Error: [changeDirection] estas intentado acceder a un arma pero la arma actual es NONE_WEAPN \n";
        return;

    }
    return this->armament.at(currentWeapon)->changeDirection(direction);
}

void Armament::unarmed() {
    this->currentWeapon = NONE_WEAPON;
}

void Armament::putWeaponOnStandBy() {
    this->weaponOnStandBy = currentWeapon;
}

void Armament::getWeaponOnStandBy() {
    this->currentWeapon = weaponOnStandBy;
    this->weaponOnStandBy = NONE_WEAPON;
}

WeaponsDTO Armament::getWeaponsDTO() const {
    std::vector<WeaponDTO> vecWeaponDTO;
    for(auto& mapWeapons : armament){
        vecWeaponDTO.push_back(mapWeapons.second->getWeaponDTO());
    }
    return WeaponsDTO(idPlayer, vecWeaponDTO);
}



