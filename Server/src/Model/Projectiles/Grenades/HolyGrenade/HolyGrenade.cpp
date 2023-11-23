//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "HolyGrenade.h"

HolyGrenade::HolyGrenade(const GameParameters &gameParameters, const int &waitTime, const TypeFocus &typeFocus)
            : Grenade(gameParameters, waitTime, typeFocus){
    fixedRotation = true;
    restitution = 0.0f;
    this->explodable = Explodable(110.0f, 8.0f, 1.5f);
}

void HolyGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_HOLY_GRENADE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}
