//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "HolyGrenade.h"

HolyGrenade::HolyGrenade(const GameParameters &gameParameters, const int &waitTime, const TypeFocus &typeFocus)
            : Grenade(gameParameters, waitTime, typeFocus){
    fixedRotation = true;
    this->explodable = Explodable(gameParameters.holyGrenadeGetMainDamage(), gameParameters.holyGrenadeGetMaxRadio(), gameParameters.holyGrenadeGetMaxImpulse());
}

void HolyGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_HOLY_GRENADE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}
