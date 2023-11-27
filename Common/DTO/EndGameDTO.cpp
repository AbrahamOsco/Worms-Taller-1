//
// Created by abraham on 18/11/23.
//

#include "EndGameDTO.h"
EndGameDTO::EndGameDTO() : DTO(END_DTO), idPlayer(0), typeResult(WON_THE_GAME) {
}


EndGameDTO::EndGameDTO(const size_t &idPlayer, const TypeResult &typeResult):
                        DTO(END_DTO), idPlayer(idPlayer), typeResult(typeResult) {
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

bool EndGameDTO::operator==(const EndGameDTO& other) const {
    return  this->opType == other.opType &&
            this->idPlayer == other.idPlayer &&
            this->typeResult == other.typeResult;
}

