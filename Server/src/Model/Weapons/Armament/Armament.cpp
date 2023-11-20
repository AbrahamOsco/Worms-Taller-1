//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Armament.h"
#include "../WeaponsWorm/Teleport.h"
#include "../WeaponsWorm/Bat.h"
#include "../../../../../Common/DTO/ProjectilesDTO.h"
#include "../WeaponsWorm/Bazooka.h"
#include "../WeaponsWorm/AirAttackDetonator.h"


Armament::Armament(const size_t &idPlayer, const GameParameters& gameParameters)
        : idPlayer(idPlayer), currentWeapon(NONE_WEAPON), weaponOnStandBy(NONE_WEAPON), gameParameters(gameParameters) {
    armament.emplace(BASEBALL_BAT, std::make_unique<Bat>(BASEBALL_BAT, gameParameters.getBatDamage(), INFINITE, gameParameters.getBatMunition(), gameParameters) );
    armament.emplace(TELEPORT, std::make_unique<Teleport>(TELEPORT, gameParameters.getTeleportDamage(), INFINITE, gameParameters.getTeleportMunition(), gameParameters));
    armament.emplace(BAZOOKA, std::make_unique<Bazooka>(BAZOOKA, gameParameters.getBazookaProjectileDamageMax(), INFINITE, gameParameters.getBazookaMunition(), gameParameters));
    // NEW WEAPON aca las nuevas armas @todo
    armament.emplace(AIR_ATTACK, std::make_unique<AirAttackDetonator>(AIR_ATTACK, 50.0f, NO_INFINITE, 2, gameParameters));

}

bool Armament::isUnarmed() const{
    return this->currentWeapon == NONE_WEAPON;
}


TypeWeapon Armament::getWeaponCurrent() const {
    return this->currentWeapon;
}

void Armament::assignWeapon(const TypeWeapon &weapon, const Direction &direction) {
    this->currentWeapon = weapon;
    /*
    if (armament.at(currentWeapon)->hasAScope()){
        //armament.at(currentWeapon)->prepareWeapon(direction);
    }
    */
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

void Armament::putWeaponOnStandByAndUnarmed() {
    if(currentWeapon != NONE_WEAPON){
        this->weaponOnStandBy = currentWeapon;
        currentWeapon = NONE_WEAPON;
    }
}


void Armament::getWeaponOnStandBy(const bool &attacked) {
    if(weaponOnStandBy != NONE_WEAPON  and not attacked){
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

ProjectilesDTO Armament::getProjectilesDTO(const bool &attackedWorm) {
    std::vector<ProjectileDTO> vecProjectileDTO;
//  si ataco (entonces el currenWeapon sera none) y la arma con la q ataco pasa a standBy si esta no lanza projectiles no  muestro nada
    if( (currentWeapon == NONE_WEAPON and weaponOnStandBy == NONE_WEAPON)  or (not attackedWorm) or (attackedWorm and not weaponStandByLaunchesProjectiles()) ){
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    armament.at(weaponOnStandBy)->getProjectilesDTO(vecProjectileDTO);
    TypeShowProjectiles typeShowProj = NO_SHOW_PROJECTILES;
    if ( not vecProjectileDTO.empty()) {
        std::cout << "Se Obtiene q existe almenos un projectil\n";
        typeShowProj = SHOW_PROJECTILES;
    }
    return ProjectilesDTO(typeShowProj, vecProjectileDTO);
}

void Armament::tryCleanProjectiles(b2World *aWorld) {
    if(weaponOnStandBy != NONE_WEAPON and armament.at(weaponOnStandBy)->launchesProjectiles()){
        armament.at(weaponOnStandBy)->tryCleanProjectiles(aWorld);
    }
}

void Armament::endTurn() {
    this->currentWeapon = NONE_WEAPON;
    this->weaponOnStandBy = NONE_WEAPON;
}

bool Armament::thereAreProjectiles() {
    if(weaponOnStandBy == NONE_WEAPON){
        return false;
    }
    return armament.at(weaponOnStandBy)->thereAreProjectiles();
}

bool Armament::weaponStandByLaunchesProjectiles() {
    if(weaponOnStandBy == NONE_WEAPON){
        return false;
    }
    return armament.at(weaponOnStandBy)->launchesProjectiles();
}

void Armament::assignWindValue(const float &aWindValue) {
    for(auto& mapWeapons: armament){
        mapWeapons.second.get()->assignWindValue(aWindValue);
    }
}

void Armament::giveExtraMunition(const size_t &extraMunition) {
    for(auto& mapWeapons: armament){
        mapWeapons.second->giveExtraMunition(extraMunition);
    }
}


