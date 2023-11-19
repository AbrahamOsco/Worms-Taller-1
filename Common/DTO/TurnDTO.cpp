//
// Created by abraham on 15/11/23.
//

#include "TurnDTO.h"
TurnDTO::TurnDTO() : DTO(OperationType::TURN_DTO){}

TurnDTO::TurnDTO(const size_t &idPlayerCurrent, const std::string &textTurn, const size_t &timeLeft, const size_t &valueWind,
                 const TypeWind &typeWind) : DTO(TURN_DTO), idPlayerCurrent(idPlayerCurrent),
                 textTurn(textTurn), timeLeft(timeLeft), valueWind(valueWind), typeWind(typeWind) {
}

size_t TurnDTO::getIdPlayerCurrent() const {
    return idPlayerCurrent;
}

std::string TurnDTO::getTextTurn() const {
    return textTurn;
}

void TurnDTO::setTextTurn(const std::string &textTurn) {
    this->textTurn = textTurn;
}

size_t TurnDTO::getTimeLeft() const {
    return timeLeft;
}

void TurnDTO::setTimeLeft(const size_t &timeLeft) {
    this->timeLeft = timeLeft;
}

void TurnDTO::setIdPlayerCurrent(const size_t &idPlayerCurrent) {
    this->idPlayerCurrent = idPlayerCurrent;
}

size_t TurnDTO::getValueWind() const {
    return valueWind;
}

void TurnDTO::setValueWind(const size_t &valueWind) {
    this->valueWind = valueWind;
}

TypeWind TurnDTO::getTypeWind() const {
    return typeWind;
}

void TurnDTO::setTypeWind(const TypeWind &typeWind) {
    this->typeWind = typeWind;
}




