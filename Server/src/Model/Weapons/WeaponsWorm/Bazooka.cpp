//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "Bazooka.h"

Bazooka::Bazooka(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
                 const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal,
                 aTypeMunition, aMunition, gameParameters), weaponSight(gameParameters.getBazookaRayLength(),
                 gameParameters.getWeaponAngleInitial(), gameParameters) {
    impulseWeapon = std::make_pair(gameParameters.BazookaGetImpulseXInitial(),
    gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.getBazookaMaxImpulseX(), gameParameters.getBazookaMaxImpulseY());
    projectil = nullptr;
    explosionIterations = gameParameters.getAnimationIterations();
}

void Bazooka::increaseAngle() {
    weaponSight.increaseAngle();
}

void Bazooka::decreaseAngle() {
    weaponSight.decreaseAngle();
}

bool Bazooka::hasAScope() {
    return true;
}

bool Bazooka::increaseImpulse() {
    impulseWeapon.first += gameParameters.getIncreaseImpulseForFPS();
    impulseWeapon.second += gameParameters.getIncreaseImpulseForFPS();
    float tolerance = 0.0001;
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance &&
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}


void Bazooka::shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction,
            const TypeFocus &focus) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseMuniBazooka = weaponSight.getImpulseForProjectil(direction, impulseWeapon);
    projectil = std::make_unique<ProjectileBazooka>(gameParameters, focus);
    projectil->addToTheWorld(world, p2, impulseMuniBazooka, windValue);
    explosionIterations = gameParameters.getAnimationIterations();
}


bool Bazooka::launchesProjectiles() {
    return true;
}

void Bazooka::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if (projectil!= nullptr && projectil->isDestroyedBody() && explosionIterations > 0) {
        ProjectileDTO projectileDto = projectil->getProjectilDTO();
        projectileDto.setTypeExplode(EXPLODE);
        if (explosionIterations == gameParameters.getAnimationIterations()) {
            projectileDto.setTypeExplode(EXPLODE_SOUND);
        }
        vecProjectileDTO.push_back(projectileDto);
        explosionIterations--;
    } else if (projectil != nullptr && !projectil->isDestroyedBody()) {
        vecProjectileDTO.push_back(projectil->getProjectilDTO());
    }
}

WeaponSightDTO Bazooka::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}

void Bazooka::tryCleanProjectiles(b2World *aWorld) {
    if (projectil!= nullptr && projectil->isDestroyedBody() && explosionIterations <= 0) {
        aWorld->DestroyBody(projectil->getBody());
        projectil = nullptr;
        impulseWeapon = std::make_pair(gameParameters.BazookaGetImpulseXInitial(),
                                       gameParameters.getBazookaImpulseYInitial());
    }
}

bool Bazooka::hasVariablePower() {
    return true;
}

bool Bazooka::thereAreProjectiles() {
    return (projectil != nullptr);
}




