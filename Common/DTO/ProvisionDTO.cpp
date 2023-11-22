//
// Created by abraham on 19/11/23.
//

#include "ProvisionDTO.h"

ProvisionDTO::ProvisionDTO() : DTO(PROVISION_DTO) {
}

ProvisionDTO::ProvisionDTO(const size_t &positionX, const size_t &positionY, const TypeEffect &typeEffect,  const TypeContact& typeContact) : DTO(PROVISION_DTO),
    positionX(positionX), positionY(positionY), typeEffect(typeEffect), typeContact(typeContact) {
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

TypeContact ProvisionDTO::getTypeContact() const {
    return typeContact;
}

void ProvisionDTO::setTypeContact(const TypeContact &typeContact) {
    this->typeContact = typeContact;
}

bool ProvisionDTO::operator==(const ProvisionDTO& other) const {
    return  this->opType == other.opType &&
            this->positionX == other.positionX &&
            this->positionY == other.positionY &&
            this->typeEffect == other.typeEffect &&
            this->typeContact == other.typeContact;
}
