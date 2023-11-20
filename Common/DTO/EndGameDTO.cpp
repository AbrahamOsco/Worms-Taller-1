//
// Created by abraham on 18/11/23.
//

#include "EndGameDTO.h"
EndGameDTO::EndGameDTO() : DTO(END_DTO) {
}


EndGameDTO::EndGameDTO(const size_t &idPlayer, const TypeResult &typeResult)  : DTO(END_DTO), idPlayer(idPlayer), typeResult(typeResult) {
}

TypeResult EndGameDTO::getTypeResult() const {
    return typeResult;
}

void EndGameDTO::setTypeResult(TypeResult typeResult) {
    this->typeResult = typeResult;
}

size_t EndGameDTO::getIdPlayer() const {
    return idPlayer;
}


