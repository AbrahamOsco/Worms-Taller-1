//
// Created by abraham on 19/11/23.
//

#include "ProvisionDTO.h"

ProvisionDTO::ProvisionDTO(const size_t &positionX, const size_t &positionY, const TypeEffect &typeEffect) : DTO(PROVISION_DTO) {

}

size_t ProvisionDTO::getPositionX() const {
    return positionX;
}

size_t ProvisionDTO::getPositionY() const {
    return positionY;
}

TypeEffect ProvisionDTO::getTypeEffect() const {
    return typeEffect;
}




