//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "Bazooka.h"

Bazooka::Bazooka(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
                 const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal,
                 aTypeMunition, aMunition, gameParameters), weaponSight(gameParameters.getBazookaRayLength(),
                 gameParameters.getWeaponAngleInitial(), gameParameters){
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(gameParameters.getBazookaMaxImpulseX(), gameParameters.getBazookaMaxImpulseY());
    projectil = nullptr;
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
    std::cout << "Incremento la potencia bazzoka\n";
    impulseWeapon.first += gameParameters.getIncreaseImpulseForFPS();
    impulseWeapon.second += gameParameters.getIncreaseImpulseForFPS();

    // para comprar floats necesitamos comprar las restas con un epsilon.
    float tolerance = 0.0001;
    bool isMaxImpulse = std::abs(impulseWeapon.first - maxImpulseWeapon.first) < tolerance and
                        std::abs(impulseWeapon.second - maxImpulseWeapon.second) < tolerance;
    return isMaxImpulse;
}


void Bazooka::shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseMuniBazooka = weaponSight.getImpulseForMuniBazooka(direction, impulseWeapon);
    //std::unique_ptr<ClientLogin> unCliente{new ClientLogin(std::move(sktPeer), games)}
    // creamos la munition de la bazooka
    std::cout << "Atacamos con la bazooka------------------------------------------------------\n";
    projectil = std::make_unique<ProjectileBazooka>(gameParameters);
    projectil->addToTheWorld(world, p2, impulseMuniBazooka, windValue);

    // reseeteamos los impulsos luego de atacar.
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(), gameParameters.getBazookaImpulseYInitial());
}


std::unique_ptr<ProjectileBazooka> * Bazooka::getProjectile(){
    return &projectil;
}

bool Bazooka::launchesProjectiles() {
    return true;
}

void Bazooka::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if(projectil == nullptr){
        return;
    }
    b2Vec2 positionProj =  projectil->getBody()->GetWorldCenter();
    ProjectileDTO projectileDto(BAZOOKA_PROJECTILE, positionProj.x * gameParameters.getPositionAdjustment() ,
                                    gameParameters.getMaxHeightPixel() - positionProj.y * gameParameters.getPositionAdjustment() );
    vecProjectileDTO.push_back(projectileDto);
}

WeaponSightDTO Bazooka::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    return weaponSight.getWeaponSightDTO(positionWorm, directionCurrent);
}

void Bazooka::tryCleanProjectiles(b2World *aWorld) {
    if(projectil!= nullptr and  projectil->isDestroyedBody()){
        aWorld->DestroyBody(projectil->getBody());
        projectil = nullptr;
    }
}

bool Bazooka::hasVariablePower() {
    return true;
}

bool Bazooka::thereAreProjectiles() {
    return (projectil != nullptr);
}




