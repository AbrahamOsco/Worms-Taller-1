//
// Created by abraham on 15/11/23.
//

#ifndef WORMS_TALLER_1_TURNDTO_H
#define WORMS_TALLER_1_TURNDTO_H


#include <cstddef>
#include <string>
#include "DTO.h"

class TurnDTO : public DTO {
private:
    size_t idPlayerCurrent;
    std::string textTurn;
    size_t timeLeft;
public:

    TurnDTO();

    TurnDTO(const size_t& idPlayerCurrent, const std::string& textTurn, const size_t& timeLeft);

    size_t getIdPlayerCurrent() const;

    void setIdPlayerCurrent(const size_t &idPlayerCurrent);

    std::string getTextTurn() const;

    void setTextTurn(const std::string &textTurn);

    size_t getTimeLeft() const;

    void setTimeLeft(const size_t &timeLeft);



};


#endif //WORMS_TALLER_1_TURNDTO_H
