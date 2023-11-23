//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "Mortar.h"
#include "../../Projectiles/Mortar/MortarMainProjectile/MortarMainProjectile.h"

Mortar::Mortar(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,const size_t &aMunition,
               const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal, aTypeMunition, aMunition,gameParameters),
                                                       weaponSight(1.0f, 0.0f, gameParameters) {
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.getBazookaMaxImpulseX(), gameParameters.getBazookaMaxImpulseY());
    projectil = nullptr;
    explosionIterations = 15;
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
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance and
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}

bool Mortar::launchesProjectiles() {
    return true;
}

bool Mortar::thereAreProjectiles() {
    return (projectil != nullptr);
}

void Mortar::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if (projectil != nullptr and projectil->isDestroyedBody() and projectil->hasExplosionIterations()) {
        projectil->getProjectileDTO(vecProjectileDTO);
        ProjectileDTO *projectileDto = &vecProjectileDTO.back(); // saco unar referencia del ultimo q pushee para setearle el typeEXplode
        projectileDto->setTypeExplode(EXPLODE);
        if (projectil->getNumberIterations() == 15.0f) {
            projectileDto->setTypeExplode(EXPLODE_SOUND);
        }
        projectil->removeAIteration();
    } else if (projectil != nullptr and not projectil->isDestroyedBody()) {
        projectil->getProjectileDTO(vecProjectileDTO);
    }

    MortarMainProjectile* mortarMain = (MortarMainProjectile*) projectil.get();
    if( mortarMain!= nullptr and  mortarMain->hasFragment()){
        mortarMain->getFragmentProjectilDTO(vecProjectileDTO);
    }
}

void Mortar::tryCleanProjectiles(b2World *aWorld) {
    MortarMainProjectile* mortarMain = (MortarMainProjectile*) projectil.get();
    if( mortarMain!= nullptr and  mortarMain->hasFragment()){
        mortarMain->tryCleanProjectiles();
    } else if ( mortarMain!= nullptr and  not mortarMain->hasFragment() and mortarMain->isDestroyedBody() and not mortarMain->hasExplosionIterations()){
        aWorld->DestroyBody(mortarMain->getBody());
        projectil = nullptr;
    }
}

WeaponSightDTO Mortar::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return Weapon::getWeaponSightDTO(positionWorm, directionCurrent);
}

void Mortar::shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction,
                             const TypeFocus &focus) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseMuniBazooka = weaponSight.getImpulseForProjectil(direction, impulseWeapon);

    std::cout << "Atacamos con el mortero------------------------------------------------------\n";
    projectil = std::make_unique<ProjectileMortar>(gameParameters, focus);
    projectil->addToTheWorld(world, p2, impulseMuniBazooka, windValue);
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
    explosionIterations = 15;
}
