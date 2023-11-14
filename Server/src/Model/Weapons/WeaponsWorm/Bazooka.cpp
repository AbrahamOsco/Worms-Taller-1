//
// Created by abraham on 13/11/23.
//

#include "Bazooka.h"

Bazooka::Bazooka(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
                 const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon, damagePrincipal,
                 aTypeMunition, aMunition, gameParameters), weaponSight(gameParameters.getBazookaRayLength(),
                 gameParameters.getWeaponAngleInitial(), gameParameters){
    impulseWeapon = std::make_pair(gameParameters.getBazookaImpulseXInitial(),
                                   gameParameters.getBazookaImpulseYInitial());
    maxImpulseWeapon = std::make_pair(1.0f, 1.0f);
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

// para incrementar el impulso OJO . @todo IMPULSO ES VARIABLE OJO !.
void Bazooka::increaseImpulse() {
    impulseWeapon.first += 0.01;
    impulseWeapon.second += 0.01;
}


void Bazooka::shootProjectile(b2World *world, const b2Vec2 &positionWorm, const Direction &direction) {
    b2Vec2 p2 = weaponSight.getPositionP2RayCast(positionWorm, direction);
    b2Vec2 impulseMuniBazooka = weaponSight.getImpulseForMuniBazooka(direction, impulseWeapon);
    //std::unique_ptr<ClientLogin> unCliente{new ClientLogin(std::move(sktPeer), games)}
    // creamos la munition de la bazooka
    std::unique_ptr <ProjectileBazooka> aProjectile{new ProjectileBazooka(gameParameters)};
    aProjectile->addToTheWorld(world, p2, impulseMuniBazooka);
    projectiles.push_back(std::move(aProjectile));
}


std::vector<std::unique_ptr<ProjectileBazooka>>* Bazooka::getProjectiles(){
    return &projectiles;
}


