//
// Created by abraham on 24/10/23.
//

#include "DTO.h"

DTO::DTO(OpType opType) : opType(opType) {}

OpType DTO::getOperationType() const {
    return opType;
}

void DTO::setOperationType(const OpType &anOpType) {
    this->opType = anOpType;
}
