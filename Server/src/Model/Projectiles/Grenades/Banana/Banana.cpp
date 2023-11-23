//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "Banana.h"
Banana::Banana(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus) :
            Grenade(gameParameters, waitTime, typeFocus){
    fixedRotation = false;
    restitution = 0.9f;
    this->explodable = Explodable(70.0f, 4.0f, 1.0f);
}

void Banana::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_BANANA, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                             gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}

