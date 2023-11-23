//
// Created by abraham on 22/11/23.
//

#include <iostream>
#include "GrenadeHolder.h"
#include "../../Projectiles/Grenades/GreenGrenade/GreenGrenade.h"

GrenadeHolder::GrenadeHolder(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition, const size_t &aMunition,
            const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal, aTypeMunition, aMunition, gameParameters),
                                                    weaponSight(3.0f, 0.0f, gameParameters) {
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.getBazookaMaxImpulseX(), gameParameters.getBazookaMaxImpulseY());
    explosionIterations = 15;
}

void GrenadeHolder::increaseAngle() {
    weaponSight.increaseAngle();
}

void GrenadeHolder::decreaseAngle() {
    weaponSight.decreaseAngle();
}

bool GrenadeHolder::hasAScope() {
    return true;
}

bool GrenadeHolder::hasVariablePower() {
    return true;
}

bool GrenadeHolder::increaseImpulse() {
    std::cout << "Incremento la potencia del lanzador de la granada\n";
    impulseWeapon.first += gameParameters.getIncreaseImpulseForFPS();
    impulseWeapon.second += gameParameters.getIncreaseImpulseForFPS();

    // para comprar floats necesitamos comprar las restas con un epsilon.
    float tolerance = 0.0001;
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance and
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}

bool GrenadeHolder::launchesProjectiles() {
    return true;
}

bool GrenadeHolder::thereAreProjectiles() {
    for(auto& aGrenade: grenades){
        if(aGrenade != nullptr ){
            return true;
        }
    }
    return false;
}

void GrenadeHolder::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for(auto& aGrenade : grenades){
        if(aGrenade != nullptr and not aGrenade->isDestroyedBody()){
            vecProjectileDTO.push_back(aGrenade->getProjectilDTO());
        }
    }
}

void GrenadeHolder::tryCleanProjectiles(b2World *aWorld) {
    for(auto& aGrenade: grenades){
        if(aGrenade!= nullptr and aGrenade->isDestroyedBody() ){
            aWorld->DestroyBody(aGrenade->getBody());
            aGrenade = nullptr;
        }
    }
}

WeaponSightDTO GrenadeHolder::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}


void GrenadeHolder::attack(const TypeWeapon &typeGrenade, const b2Vec2 &positionWorm, const Direction &direction,
                           const TypeFocus &typeFocus, const int &timeWait, b2World *world) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseForGrenade = weaponSight.getImpulseForProjectil(direction, impulseWeapon);
    std::cout << "Atacamos con el grenadeHolder ------------------------------------------------------\n";
    if(typeGrenade == GREEN_GRENADE){
        std::unique_ptr<Grenade> grenade{new GreenGrenade(gameParameters, timeWait, typeFocus)};
        grenade->addToTheWorld(world, p2, impulseForGrenade);
        grenades.push_back(std::move(grenade));
    }
    weaponSight.resetRayCast();
}

void GrenadeHolder::passTime() {
    for(auto& aGrenade : grenades){
        if(aGrenade != nullptr){
            aGrenade->passTime();
        }
    }
}


