//
// Created by abraham on 23/11/23.
//

#include <vector>
#include "MortarFragment.h"

MortarFragment::MortarFragment(const GameParameters &gameParameters, const TypeFocus &typeFocus) : ProjectileMortar(
        gameParameters, typeFocus) {
    this->explodable = Explodable(gameParameters.mortarFragmentGetMainDamage(),
    gameParameters.mortarFragmentGetMaxRadio(), gameParameters.mortarFragmentGetMaxImpulse());
}

void MortarFragment::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    vecProjectileDTO.push_back(ProjectileDTO(PROJ_MORTAR_FRAGMENT,
    this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
    gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                              this->typeFocus, NO_EXPLODE) );
}
