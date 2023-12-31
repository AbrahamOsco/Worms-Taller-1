//
// Created by abraham on 14/11/23.
//

#include "ProjectileDTO.h"

ProjectileDTO::ProjectileDTO() : DTO(PROJECTILE_DTO), typeProjectil(NONE_PROJECTILE), positionX(0),
                            positionY(0), typeFocus(NO_FOCUS), typeExplode(NO_EXPLODE) {
}

ProjectileDTO::ProjectileDTO(const TypeProjectil &typeProjectil, const size_t &positionX, const size_t &positionY,
                             const TypeFocus &typeFocus, const TypeExplode& typeExplode) :
                DTO(PROJECTILE_DTO), typeProjectil(typeProjectil), positionX(positionX),
                positionY(positionY), typeFocus(typeFocus), typeExplode(typeExplode) {
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

TypeFocus ProjectileDTO::getTypeFocus() const {
    return typeFocus;
}

TypeExplode ProjectileDTO::getTypeExplode() const {
    return typeExplode;
}

void ProjectileDTO::setTypeExplode(const TypeExplode &typeExplode) {
    this->typeExplode = typeExplode;
}

bool ProjectileDTO::operator==(const ProjectileDTO& other) const {
    return  this->opType == other.opType &&
            this->typeProjectil == other.typeProjectil &&
            this->positionX == other.positionX &&
            this->positionY == other.positionY &&
            this->typeFocus == other.typeFocus &&
            this->typeExplode == other.typeExplode;
}
