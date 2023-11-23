//
// Created by abraham on 22/11/23.
//

#include <iostream>
#include "GreenGrenade.h"
// Aca ponemos el danio main, radio y el impulso explosion.

GreenGrenade::GreenGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus) : Grenade(gameParameters, waitTime, typeFocus) {
    fixedRotation = true;
    restitution = 0.0f;
    this->explodable = Explodable(40.0f, 2.0f, 3.0f);
}

void GreenGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_GREEN_GRENADE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}


