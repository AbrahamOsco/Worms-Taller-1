//
// Created by abraham on 24/10/23.
//

#include "DTO.h"

DTO::DTO(OperationType opType) : opType(opType) {}

OperationType DTO::getOperationType() const {
    return opType;
}

void DTO::setOperationType(const OperationType &anOpType) {
    this->opType = anOpType;
}
bool DTO::operator==(const DTO& other) const {
    return this->opType == other.opType;
}