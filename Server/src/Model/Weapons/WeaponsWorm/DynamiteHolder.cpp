//
// Created by abraham on 21/11/23.
//

#include "DynamiteHolder.h"

DynamiteHolder::DynamiteHolder(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition, const size_t &aMunition,
              const GameParameters &gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition, gameParameters),
              dynamite(nullptr) {
}

void DynamiteHolder::placeDynamite(const int &waitTime, const b2Vec2 &positionDynamite, b2World *world,
                                   const TypeFocus &typeFocus) {
    dynamite = std::make_unique<Dynamite>(waitTime, gameParameters, typeFocus);
    dynamite->addToTheWorld(world, positionDynamite);
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
        aWorld->DestroyBody(dynamite->getBody());
        dynamite = nullptr;
    }
}

void DynamiteHolder::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if(dynamite != nullptr){
        vecProjectileDTO.push_back(dynamite->getProjectilDTO());
    }
}


