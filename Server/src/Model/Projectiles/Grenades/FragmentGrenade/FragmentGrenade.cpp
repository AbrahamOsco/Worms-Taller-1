//
// Created by abraham on 23/11/23.
//

#include "FragmentGrenade.h"

FragmentGrenade::FragmentGrenade(const GameParameters &gameParameters, const int &waitTime,
                                 const TypeFocus &typeFocus) : Grenade(gameParameters, waitTime, typeFocus) {
    fixedRotation = true;
    restitution = 0.0f;
    this->explodable = Explodable(10.0f, 3.0f, 0.5f);
}


void FragmentGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_RED_GRENADE_FRAGMENT, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}
