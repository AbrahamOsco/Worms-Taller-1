//
// Created by abraham on 21/11/23.
//

#include "DynamiteHolder.h"

DynamiteHolder::DynamiteHolder(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition, const size_t &aMunition,
              const GameParameters &gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition, gameParameters),
              dynamite(nullptr) {
}

void DynamiteHolder::placeDynamite(const int &waitTime, const b2Vec2 &positionWorm, const Direction &aDirectionWorm,b2World *world,const TypeFocus &typeFocus) {
    float offset = -0.5f;
    if (aDirectionWorm == RIGHT){
        offset = 1.0;
    }
    b2Vec2 positionDynamite(positionWorm.x + offset, positionWorm.y);
    dynamite = std::make_unique<Dynamite>(waitTime, gameParameters, typeFocus);
    dynamite->addToTheWorld(world, positionDynamite);
    sendLastDTO = false;
}

bool DynamiteHolder::hasAScope() {
    return false;
}

bool DynamiteHolder::hasVariablePower() {
    return false;
}

bool DynamiteHolder::launchesProjectiles() {
    return true;
}

bool DynamiteHolder::thereAreProjectiles() {
    return this->dynamite != nullptr;
}

void DynamiteHolder::tryCleanProjectiles(b2World *aWorld) {
    if(dynamite != nullptr and dynamite->isDestroyedBody()){
        lastProjectilDTO = dynamite->getProjectilDTO();
        lastProjectilDTO.setTypeExplode(EXPLODE);
        aWorld->DestroyBody(dynamite->getBody());
        dynamite = nullptr;
    }
}

void DynamiteHolder::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if(dynamite == nullptr and not sendLastDTO){
        vecProjectileDTO.push_back(lastProjectilDTO);
        sendLastDTO = true;
        return;
    }
    if(dynamite != nullptr){
        vecProjectileDTO.push_back(dynamite->getProjectilDTO());
    }
}

void DynamiteHolder::passTime() {
    if(dynamite != nullptr){
        dynamite->passTime();
    }
}



