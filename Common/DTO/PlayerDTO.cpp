//
// Created by abraham on 31/10/23.
//

#include "PlayerDTO.h"

PlayerDTO::PlayerDTO() : DTO(PLAYER) {

}

PlayerDTO::PlayerDTO(const size_t &idPlayer, const std::string &aNamePlayer, const TurnType &aTurnType,
                     const size_t &aTotalHPWorms) : DTO(PLAYER), idPlayer(idPlayer), namePlayer(aNamePlayer), turnType(aTurnType), totalHPWorms(aTotalHPWorms)  {

}


size_t PlayerDTO::getIdPlayer() const {
    return idPlayer;
}

TurnType PlayerDTO::getTurnType() const {
    return turnType;
}

std::string PlayerDTO::getNamePlayer() const {
    return namePlayer;
}

size_t PlayerDTO::getTotalHpWorms() const {
    return totalHPWorms;
}

void PlayerDTO::setIdPlayer(const size_t &idPlayer) {
    this->idPlayer = idPlayer;
}

void PlayerDTO::setNamePlayer(const std::string &namePlayer) {
    this->namePlayer = namePlayer;
}

void PlayerDTO::setTurnType(const TurnType &turnType) {
    this->turnType = turnType;
}

void PlayerDTO::setTotalHpWorms(const size_t &totalHpWorms) {
    this->totalHPWorms = totalHpWorms;
}

bool PlayerDTO::operator==(const PlayerDTO& other) const {
    return  this->opType == other.opType &&
            this->idPlayer == other.idPlayer &&
            this->namePlayer == other.namePlayer &&
            this->turnType == other.turnType &&
            this->totalHPWorms == other.totalHPWorms;
}
