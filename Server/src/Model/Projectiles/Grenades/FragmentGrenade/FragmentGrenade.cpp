//
// Created by abraham on 23/11/23.
//

#include "FragmentGrenade.h"

FragmentGrenade::FragmentGrenade(const GameParameters &gameParameters, const int &waitTime,
                                 const TypeFocus &typeFocus) : Grenade(gameParameters, waitTime, typeFocus) {
    fixedRotation = true;
    this->explodable = Explodable(gameParameters.redGrenadeFragmentGetMainDamage(),
                                  gameParameters.redGrenadeFragmentGetMaxRadio(),
                                  gameParameters.redGrenadeFragmentGetMaxImpulse());
}


void FragmentGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_RED_GRENADE_FRAGMENT, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}
