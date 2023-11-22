//
// Created by abraham on 13/11/23.
//

#include "WeaponSightDTO.h"

WeaponSightDTO::WeaponSightDTO() : DTO(WEAPON_SIGHT) {
}

WeaponSightDTO::WeaponSightDTO(const TypeSight &typeSight, const size_t &positionXSight, const size_t positionYSight) : DTO(WEAPON_SIGHT), typeSight(typeSight),
                positionXSight(positionXSight), positionYSight(positionYSight){
}


TypeSight WeaponSightDTO::getTypeSight() const {
    return typeSight;
}

size_t WeaponSightDTO::getPositionXSight() const {
    return positionXSight;
}

size_t WeaponSightDTO::getPositionYSight() const {
    return positionYSight;
}

void WeaponSightDTO::setTypeSight(const TypeSight &typeSight) {
    this->typeSight = typeSight;
}

void WeaponSightDTO::setPositionXSight(const size_t &positionXSight) {
    this->positionXSight = positionXSight;
}

void WeaponSightDTO::setPositionYSight(const size_t &positionYSight) {
    this->positionYSight = positionYSight;
}

bool WeaponSightDTO::operator==(const WeaponSightDTO& other) const {
    return  this->opType == other.opType &&
            this->positionXSight == other.positionXSight &&
            this->positionYSight == other.positionYSight &&
            this->typeSight == other.typeSight;
}

