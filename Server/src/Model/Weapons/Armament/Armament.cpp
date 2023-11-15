//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Armament.h"
#include "../WeaponsWorm/Teleport.h"
#include "../WeaponsWorm/Bat.h"
#include "../../../../../Common/DTO/ProjectilesDTO.h"
#include "../WeaponsWorm/Bazooka.h"


Armament::Armament(const size_t &idPlayer, const GameParameters& gameParameters)
        : idPlayer(idPlayer), currentWeapon(NONE_WEAPON), weaponOnStandBy(NONE_WEAPON), gameParameters(gameParameters) {
    armament.emplace(BASEBALL_BAT, std::make_unique<Bat>(BASEBALL_BAT, gameParameters.getBatDamage(), INFINITE, gameParameters.getBatMunition(), gameParameters) );
    armament.emplace(TELEPORT, std::make_unique<Teleport>(TELEPORT, gameParameters.getTeleportDamage(), INFINITE, gameParameters.getTeleportMunition(), gameParameters));
    armament.emplace(BAZOOKA, std::make_unique<Bazooka>(BAZOOKA, gameParameters.getBazookaProjectileDamageMax(), INFINITE, gameParameters.getBazookaMunition(), gameParameters));


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
        //armament.at(currentWeapon)->prepareWeapon(direction);
    }
}

Weapon * Armament::getWeaponCurrentPtr() {
    return armament.at(currentWeapon).get();
}

bool Armament::hasAScoped() {
    if(this->currentWeapon == NONE_WEAPON){
        std::cerr << "Error: [hasAScoped] estas intentado acceder a un arma pero la arma actual es NONE_WEAPN \n";
    }
    return this->armament.at(currentWeapon)->hasAScope();
}

/*
// quizas lo saquemos?
void Armament::changeDirection(const Direction &direction) {
    if(this->currentWeapon == NONE_WEAPON){
        // en el caso de que estamos desarmado no hacemos nada.
        std::cerr << "Error: [changeDirection] estas intentado acceder a un arma pero la arma actual es NONE_WEAPN \n";
        return;

    }
    return this->armament.at(currentWeapon)->changeDirection(direction);
}
*/

void Armament::putWeaponOnStandByAndUnarmed() {
    if(currentWeapon != NONE_WEAPON){
        this->weaponOnStandBy = currentWeapon;
        currentWeapon = NONE_WEAPON;
    }
}

void Armament::getWeaponOnStandBy() {
    if(weaponOnStandBy != NONE_WEAPON){
        this->currentWeapon = weaponOnStandBy;
        this->weaponOnStandBy = NONE_WEAPON;
    }
}

WeaponsDTO Armament::getWeaponsDTO() const {
    std::vector<WeaponDTO> vecWeaponDTO;
    for(auto& mapWeapons : armament){
        vecWeaponDTO.push_back(mapWeapons.second->getWeaponDTO());
    }
    TypeWeapon aCurrentWP;
    if(currentWeapon == NONE_WEAPON and weaponOnStandBy != NONE_WEAPON){
        aCurrentWP = weaponOnStandBy;
    } else if ( currentWeapon != NONE_WEAPON and weaponOnStandBy == NONE_WEAPON){
        aCurrentWP = currentWeapon;
    } else if ( currentWeapon == NONE_WEAPON and weaponOnStandBy == NONE_WEAPON){
        aCurrentWP = currentWeapon;
    }
    return WeaponsDTO(idPlayer, vecWeaponDTO, aCurrentWP);
}

WeaponSightDTO Armament::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    if( currentWeapon == NONE_WEAPON){
        return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
    }
    return armament.at(currentWeapon)->getWeaponSightDTO(positionWorm, directionCurrent);
}

ProjectilesDTO Armament::getProjectilesDTO(){
    std::vector<ProjectileDTO> vecProjectileDTO;
    if (currentWeapon == NONE_WEAPON or (not this->armament.at(currentWeapon)->launchesProjectiles()) ){
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    armament.at(currentWeapon)->getProjectilesDTO(vecProjectileDTO);
    TypeShowProjectiles typeShowProj = NO_SHOW_PROJECTILES;
    if (vecProjectileDTO.size() > 0){
        typeShowProj = SHOW_PROJECTILES;
    }
    return ProjectilesDTO(typeShowProj, vecProjectileDTO);
}


