//
// Created by abraham on 15/11/23.
//

#include "TurnDTO.h"

TurnDTO::TurnDTO(const size_t &idPlayerCurrent, const std::string &textTurn, const size_t &timeLeft) : DTO(TURN_DTO),
                                            idPlayerCurrent(idPlayerCurrent), textTurn(textTurn), timeLeft(timeLeft){
}

size_t TurnDTO::getIdPlayerCurrent() const {
    return idPlayerCurrent;
}

void TurnDTO::setIdPlayerCurrent(const size_t &idPlayerCurrent) {
    this->idPlayerCurrent = idPlayerCurrent;
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

TurnDTO::TurnDTO() : DTO(OperationType::TURN_DTO){}



