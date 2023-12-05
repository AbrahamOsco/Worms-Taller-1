//
// Created by abraham on 22/11/23.
//

#include <vector>
#include "GreenGrenade.h"

GreenGrenade::GreenGrenade(const GameParameters &gameParameters, const int& waitTime,
                const TypeFocus& typeFocus) : Grenade(gameParameters, waitTime, typeFocus) {
    fixedRotation = true;
    this->explodable = Explodable(gameParameters.greenGrenadeMainDamage(),
    gameParameters.greenGrenadeMaxRadio(), gameParameters.greenGrenadeMaxImpulse());
}

void GreenGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_GREEN_GRENADE,
    this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
    gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
    this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}


