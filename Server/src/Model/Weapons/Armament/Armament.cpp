//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include <vector>
#include "Armament.h"
#include "../WeaponsWorm/Teleport.h"
#include "../WeaponsWorm/Bat.h"
#include "../../../../../Common/DTO/ProjectilesDTO.h"
#include "../WeaponsWorm/Bazooka.h"
#include "../WeaponsWorm/AirAttackDetonator.h"
#include "../WeaponsWorm/DynamiteHolder.h"
#include "../WeaponsWorm/GrenadeHolder.h"
#include "../../Projectiles/Grenades/RedGrenade/RedGrenade.h"
#include "../WeaponsWorm/Mortar.h"


Armament::Armament(const size_t &idPlayer, const GameParameters& gameParameters)
        : idPlayer(idPlayer), currentWeapon(NONE_WEAPON), weaponOnStandBy(NONE_WEAPON), gameParameters(gameParameters) {
    armament.emplace(BASEBALL_BAT, std::make_unique<Bat>(BASEBALL_BAT, gameParameters.getBatDamage(),
    INFINITE, gameParameters.getBatMunition(), gameParameters) );
    armament.emplace(TELEPORT, std::make_unique<Teleport>(TELEPORT, gameParameters.getTeleportDamage(),
    INFINITE, gameParameters.getTeleportMunition(), gameParameters));
    armament.emplace(BAZOOKA, std::make_unique<Bazooka>(BAZOOKA, gameParameters.getBazookaProjectileDamageMax(),
    INFINITE, gameParameters.getBazookaMunition(), gameParameters));
    // NEW WEAPON aca las nuevas armas @todo
    armament.emplace(AIR_ATTACK, std::make_unique<AirAttackDetonator>
        (AIR_ATTACK, gameParameters.airAttackMissileGetDamage(), NO_INFINITE,
        gameParameters.airAttackGetMunitionInitial(), gameParameters));
    armament.emplace(DYNAMITE_HOLDER, std::make_unique<DynamiteHolder>(DYNAMITE_HOLDER,
        gameParameters.dynamiteGetMainDamage(), NO_INFINITE, gameParameters.dynamiteGetMunitionInitial(),
        gameParameters));
    armament.emplace(GREEN_GRENADE, std::make_unique<GrenadeHolder>(GREEN_GRENADE,
        gameParameters.greenGrenadeMainDamage(), INFINITE, gameParameters.greenGrenadeMunitionInitial(),
        gameParameters));
    armament.emplace(BANANA, std::make_unique<GrenadeHolder>(BANANA, gameParameters.bananaGetMainDamage(),
        INFINITE, gameParameters.bananaGetMunitionInitial(), gameParameters));
    armament.emplace(HOLY_GRENADE, std::make_unique<GrenadeHolder>(HOLY_GRENADE,
        gameParameters.holyGrenadeGetMainDamage(), NO_INFINITE,
        gameParameters.holyGrenadeGetMunitionInitial(), gameParameters));
    armament.emplace(RED_GRENADE, std::make_unique<GrenadeHolder>(RED_GRENADE,
        gameParameters.redGrenadeGetMainDamage(), NO_INFINITE, gameParameters.redGrenadeGetMunitionInitial(),
        gameParameters));
    armament.emplace(MORTAR, std::make_unique<Mortar>(MORTAR, gameParameters.mortarGetMainDamage(),
        NO_INFINITE, gameParameters.mortartGetMunitionInitial(), gameParameters) );
}

bool Armament::isUnarmed() const {
    return this->currentWeapon == NONE_WEAPON;
}


TypeWeapon Armament::getWeaponCurrent() const {
    return this->currentWeapon;
}

void Armament::assignWeapon(const TypeWeapon &weapon, const Direction &direction) {
    this->currentWeapon = weapon;
}

Weapon * Armament::getWeaponCurrentPtr() {
    return armament.at(currentWeapon).get();
}

void Armament::putWeaponOnStandByAndUnarmed() {
    if (currentWeapon != NONE_WEAPON) {
        this->weaponOnStandBy = currentWeapon;
        currentWeapon = NONE_WEAPON;
    }
}


void Armament::getWeaponOnStandBy(const bool &attacked) {
    if (weaponOnStandBy != NONE_WEAPON  && !attacked) {
        this->currentWeapon = weaponOnStandBy;
        this->weaponOnStandBy = NONE_WEAPON;
    }
}

WeaponsDTO Armament::getWeaponsDTO() const {
    std::vector<WeaponDTO> vecWeaponDTO;
    for (auto& mapWeapons : armament) {
        vecWeaponDTO.push_back(mapWeapons.second->getWeaponDTO());
    }
    TypeWeapon aCurrentWP = NONE_WEAPON;
    if (currentWeapon == NONE_WEAPON && weaponOnStandBy != NONE_WEAPON) {
        aCurrentWP = weaponOnStandBy;
    } else if (currentWeapon != NONE_WEAPON && weaponOnStandBy == NONE_WEAPON) {
        aCurrentWP = currentWeapon;
    } else if (currentWeapon == NONE_WEAPON && weaponOnStandBy == NONE_WEAPON) {
        aCurrentWP = currentWeapon;
    }
    return WeaponsDTO(idPlayer, vecWeaponDTO, aCurrentWP);
}

WeaponSightDTO Armament::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    if (currentWeapon == NONE_WEAPON) {
        return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
    }
    return armament.at(currentWeapon)->getWeaponSightDTO(positionWorm, directionCurrent);
}

ProjectilesDTO Armament::getProjectilesDTO(const bool &attackedWorm) {
    std::vector<ProjectileDTO> vecProjectileDTO;
    if ( (currentWeapon == NONE_WEAPON && weaponOnStandBy == NONE_WEAPON)  || (!attackedWorm) ||
        (attackedWorm && !weaponStandByLaunchesProjectiles()) ) {
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    armament.at(weaponOnStandBy)->getProjectilesDTO(vecProjectileDTO);
    TypeShowProjectiles typeShowProj = NO_SHOW_PROJECTILES;
    if (!vecProjectileDTO.empty()) {
                   std::cout << "Se Obtiene q existe almenos un projectil\n";
        typeShowProj = SHOW_PROJECTILES;
    }
    return ProjectilesDTO(typeShowProj, vecProjectileDTO);
}

void Armament::tryCleanProjectiles(b2World *aWorld) {
    if (weaponOnStandBy != NONE_WEAPON && armament.at(weaponOnStandBy)->launchesProjectiles()) {
        armament.at(weaponOnStandBy)->tryCleanProjectiles(aWorld);
    }
}

void Armament::endTurn() {
    this->currentWeapon = NONE_WEAPON;
    this->weaponOnStandBy = NONE_WEAPON;
}

bool Armament::thereAreProjectiles() {
    if (weaponOnStandBy == NONE_WEAPON) {
        return false;
    }
    return armament.at(weaponOnStandBy)->thereAreProjectiles();
}

bool Armament::weaponStandByLaunchesProjectiles() {
    if (weaponOnStandBy == NONE_WEAPON) {
        return false;
    }
    return armament.at(weaponOnStandBy)->launchesProjectiles();
}

void Armament::assignWindValue(const float &aWindValue) {
    for (auto& mapWeapons : armament) {
        mapWeapons.second.get()->assignWindValue(aWindValue);
    }
}

void Armament::giveExtraMunition(const size_t &extraMunition) {
    for (auto& mapWeapons : armament) {
        mapWeapons.second->giveExtraMunition(extraMunition);
    }
}

void Armament::updateTime(const bool &attacked) {
    if (attacked && weaponOnStandBy!= NONE_WEAPON) {
        this->armament.at(weaponOnStandBy)->passTime();
    }
}

bool Armament::hasMunition() {
    return this->armament.at(currentWeapon).get()->hasMunition();
}

bool Armament::isAGrenade() const {
    return (this->currentWeapon == BANANA || this->currentWeapon == GREEN_GRENADE || this->currentWeapon == RED_GRENADE
           || this->currentWeapon == HOLY_GRENADE);
}

void Armament::attackWithGrenade(const b2Vec2 &positionWorm, const Direction &direction, const TypeFocus &focus,
                                 const int &waitTime, b2World *aWorld) {
    GrenadeHolder* grenadeHolder =  (GrenadeHolder*) armament.at(currentWeapon).get();
    grenadeHolder->attack(currentWeapon, positionWorm, direction, focus, waitTime, aWorld);
}



