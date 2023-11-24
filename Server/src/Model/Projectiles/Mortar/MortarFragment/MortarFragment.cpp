//
// Created by abraham on 23/11/23.
//

#include "MortarFragment.h"

MortarFragment::MortarFragment(const GameParameters &gameParameters, const TypeFocus &typeFocus) : ProjectileMortar(
        gameParameters, typeFocus){
    this->explodable = Explodable(10.0f, 2.0f, 1.0f);
}

void MortarFragment::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    vecProjectileDTO.push_back(ProjectileDTO(PROJ_MORTAR_FRAGMENT, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                              gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                              this->typeFocus, NO_EXPLODE) );

}
