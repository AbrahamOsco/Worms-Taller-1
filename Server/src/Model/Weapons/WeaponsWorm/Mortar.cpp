//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "Mortar.h"
#include "../../Projectiles/Mortar/MortarMainProjectile/MortarMainProjectile.h"

Mortar::Mortar(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
            const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon,
            damagePrincipal, aTypeMunition, aMunition, gameParameters),
            weaponSight(gameParameters.mortarGetRayLength(), gameParameters.getWeaponAngleInitial(), gameParameters) {
    impulseWeapon = std::make_pair(gameParameters.BazookaGetImpulseXInitial(),
            gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.getBazookaMaxImpulseX(), gameParameters.getBazookaMaxImpulseY());
    projectil = nullptr;
}

void Mortar::increaseAngle() {
    weaponSight.increaseAngle();
}

void Mortar::decreaseAngle() {
    weaponSight.decreaseAngle();
}

bool Mortar::hasAScope() {
    return true;
}

bool Mortar::hasVariablePower() {
    return true;
}

bool Mortar::increaseImpulse() {
    std::cout << "Incremento la potencia bazzoka\n";
    impulseWeapon.first += gameParameters.getIncreaseImpulseForFPS();
    impulseWeapon.second += gameParameters.getIncreaseImpulseForFPS();

    // para comprar floats necesitamos comprar las restas con un epsilon.
    float tolerance = 0.0001;
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance &&
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}

bool Mortar::launchesProjectiles() {
    return true;
}

bool Mortar::thereAreProjectiles() {
    if (projectil != nullptr) {
        MortarMainProjectile* mortarMain = (MortarMainProjectile*) projectil.get();
        if (mortarMain->hasFragment()) {
            mortarMain->awakenFragments();
        }
    }
    return (projectil != nullptr);
}

void Mortar::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if (projectil != nullptr && projectil->isDestroyedBody() && projectil->hasExplosionIterations()) {
        projectil->getProjectileDTO(vecProjectileDTO);
        ProjectileDTO *projectileDto = &vecProjectileDTO.back();
        // saco unar referencia del ultimo q pushee para setearle el typeEXplode
        projectileDto->setTypeExplode(EXPLODE);
        if (projectil->getNumberIterations() == 15.0f) {
            projectileDto->setTypeExplode(EXPLODE_SOUND);
        }
        projectil->removeAIteration();
    } else if (projectil != nullptr && !projectil->isDestroyedBody()) {
        projectil->getProjectileDTO(vecProjectileDTO);
    }

    MortarMainProjectile* mortarMain = (MortarMainProjectile*) projectil.get();
    if (mortarMain!= nullptr &&  mortarMain->hasFragment()) {
        mortarMain->getFragmentProjectilDTO(vecProjectileDTO);
    }
}

void Mortar::tryCleanProjectiles(b2World *aWorld) {
    MortarMainProjectile* mortarMain = (MortarMainProjectile*) projectil.get();
    if (mortarMain!= nullptr &&  mortarMain->hasFragment()) {
        mortarMain->tryCleanProjectiles();
    } else if (mortarMain!= nullptr &&  !mortarMain->hasFragment() &&
            mortarMain->isDestroyedBody() && !mortarMain->hasExplosionIterations()) {
        aWorld->DestroyBody(mortarMain->getBody());
        projectil = nullptr;
    }
}

WeaponSightDTO Mortar::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}

void Mortar::shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction,
                             const TypeFocus &focus) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseMuniBazooka = weaponSight.getImpulseForProjectil(direction, impulseWeapon);

    std::cout << "Atacamos con el mortero------------------------------------------------------\n";
    projectil = std::make_unique<MortarMainProjectile>(gameParameters, focus);
    projectil->addToTheWorld(world, p2, impulseMuniBazooka, windValue);
    impulseWeapon = std::make_pair(gameParameters.BazookaGetImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
    this->munition--;
}
