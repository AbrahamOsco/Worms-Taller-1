//
// Created by abraham on 22/11/23.
//

#include <iostream>
#include "GrenadeHolder.h"
#include "../../Projectiles/Grenades/GreenGrenade/GreenGrenade.h"
#include "../../Projectiles/Grenades/Banana/Banana.h"
#include "../../Projectiles/Grenades/HolyGrenade/HolyGrenade.h"
#include "../../Projectiles/Grenades/RedGrenade/RedGrenade.h"

GrenadeHolder::GrenadeHolder(const TypeWeapon &aTypeWeapon, const float &damagePrincipal,
            const TypeMunition &aTypeMunition, const size_t &aMunition,
            const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal, aTypeMunition,
            aMunition, gameParameters), weaponSight(gameParameters.grenadeGetRayLength(),
            gameParameters.getWeaponAngleInitial(), gameParameters) {
    impulseWeapon = std::make_pair(gameParameters.grenadeGetImpulseXInitial(),
        gameParameters.grenadeGetImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.grenadeGetMaxImpulseX(), gameParameters.grenadeGetMaxImpulseY());
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
    impulseWeapon.first += gameParameters.getIncreaseImpulseForFPS();
    impulseWeapon.second += gameParameters.getIncreaseImpulseForFPS();

    float tolerance = 0.0001;
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance &&
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}

bool GrenadeHolder::launchesProjectiles() {
    return true;
}

bool GrenadeHolder::thereAreProjectiles() {
    return (grenade != nullptr);
}

void GrenadeHolder::getProjectilesDTOPrimary(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if (grenade != nullptr && grenade->isDestroyedBody() && grenade->hasExplosionIterations()) {
        grenade->getProjectileDTO(vecProjectileDTO);
        ProjectileDTO *projectileDto = &vecProjectileDTO.back();
        projectileDto->setTypeExplode(EXPLODE);
        if (grenade->getNumberIterations() == gameParameters.getAnimationIterations()) {
            projectileDto->setTypeExplode(EXPLODE_SOUND);
        }
        grenade->removeAIteration();
    } else if (grenade != nullptr && !grenade->isDestroyedBody()) {
        grenade->getProjectileDTO(vecProjectileDTO);
    }
}

void GrenadeHolder::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    getProjectilesDTOPrimary(vecProjectileDTO);
    if (typeWeapon == RED_GRENADE) {
        RedGrenade* redGrenade = (RedGrenade*) grenade.get();
        if (redGrenade!= nullptr &&  redGrenade->hasFragment()) {
            redGrenade->getFragmentProjectilDTO(vecProjectileDTO);
        }
    }
}

void GrenadeHolder::tryCleanProjectiles(b2World *aWorld) {
    if (typeWeapon != RED_GRENADE) {
        if (grenade != nullptr && grenade->isDestroyedBody() && !grenade->hasExplosionIterations()) {
            resetGrenade(aWorld);
        }
        return;
    }
    RedGrenade* redGrenade = (RedGrenade*) grenade.get();
    if (redGrenade!= nullptr &&  redGrenade->hasFragment()) {
        redGrenade->tryCleanProjectiles();
    } else if ( redGrenade!= nullptr &&  !redGrenade->hasFragment() && grenade->isDestroyedBody() &&
            !grenade->hasExplosionIterations()) {
        resetGrenade(aWorld);
    }
}

void GrenadeHolder::resetGrenade(b2World *aWorld) {
    aWorld->DestroyBody(grenade->getBody());
    grenade = nullptr;
    impulseWeapon = std::make_pair(gameParameters.grenadeGetImpulseXInitial(),
                                   gameParameters.grenadeGetImpulseYInitial());
}

WeaponSightDTO GrenadeHolder::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}

void GrenadeHolder::attack(const TypeWeapon &typeGrenade, const b2Vec2 &positionWorm, const Direction &direction,
                           const TypeFocus &typeFocus, const int &timeWait, b2World *world) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseForGrenade = weaponSight.getImpulseForProjectil(direction, impulseWeapon);
    if (typeGrenade == GREEN_GRENADE) {
        grenade = std::make_unique<GreenGrenade>(gameParameters, timeWait, typeFocus);
    } else if (typeGrenade == BANANA) {
        grenade = std::make_unique<Banana>(gameParameters, timeWait, typeFocus);
    } else if (typeGrenade == HOLY_GRENADE) {
        grenade = std::make_unique<HolyGrenade>(gameParameters, timeWait, typeFocus);
        this->munition--;
    } else if (typeGrenade == RED_GRENADE) {
        grenade = std::make_unique<RedGrenade>(gameParameters, timeWait, typeFocus);
        this->munition--;
    }
    grenade->addToTheWorld(world, p2, impulseForGrenade);
    weaponSight.resetRayCast();
}

void GrenadeHolder::passTime() {
    if (grenade != nullptr) {
        grenade->passTime();
    }
}

bool GrenadeHolder::hasMunition() const {
    if (this->typeMunition == INFINITE) {
        return true;
    }
    return (munition > 0 );
}


