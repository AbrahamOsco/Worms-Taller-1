//
// Created by abraham on 18/11/23.
//

#include "EndGameDTO.h"
EndGameDTO::EndGameDTO() : DTO(END_DTO) {
}


EndGameDTO::EndGameDTO(const TypeResult &typeResult) :DTO(END_DTO), typeResult(typeResult) {
}


TypeResult EndGameDTO::getTypeResult() const {
    return typeResult;
}

void EndGameDTO::setTypeResult(TypeResult typeResult) {
    this->typeResult = typeResult;
}


