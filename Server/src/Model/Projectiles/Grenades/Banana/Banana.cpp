//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include <vector>
#include "Banana.h"
Banana::Banana(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus) :
            Grenade(gameParameters, waitTime, typeFocus) {
    fixedRotation = false;
    restitution = gameParameters.bananaGetRestitution();
    this->explodable = Explodable(gameParameters.bananaGetMainDamage(),
    gameParameters.bananaGetMaxRadio(), gameParameters.bananaGetMaxImpulse());
}

void Banana::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_BANANA,
    this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
    gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                             this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}

