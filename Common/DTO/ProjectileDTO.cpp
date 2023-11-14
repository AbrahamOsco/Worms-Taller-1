//
// Created by abraham on 14/11/23.
//

#include "ProjectileDTO.h"

ProjectileDTO::ProjectileDTO(const TypeProjectil &typeProjectil, const size_t &positionX, const size_t &positionY) :
                DTO(PROJECTILE_DTO), typeProjectil(typeProjectil), positionX(positionX), positionY(positionY){
}


TypeProjectil ProjectileDTO::getTypeProjectil() const {
    return typeProjectil;
}

void ProjectileDTO::setTypeProjectil(const TypeProjectil &typeProjectil) {
    this->typeProjectil = typeProjectil;
}

size_t ProjectileDTO::getPositionX() const {
    return positionX;
}

void ProjectileDTO::setPositionX(const size_t &positionX) {
    this->positionX = positionX;
}

size_t ProjectileDTO::getPositionY() const {
    return positionY;
}

void ProjectileDTO::setPositionY(const size_t &positionY) {
    this->positionY = positionY;
}

