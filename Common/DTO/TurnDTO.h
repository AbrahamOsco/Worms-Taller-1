//
// Created by abraham on 15/11/23.
//

#ifndef WORMS_TALLER_1_TURNDTO_H
#define WORMS_TALLER_1_TURNDTO_H


#include <cstddef>
#include <string>
#include "DTO.h"
enum TypeWind{
    WIND_LEFT, WIND_RIGHT
};

class TurnDTO : public DTO {
 private:
    size_t idPlayerCurrent;
    std::string textTurn;
    size_t timeLeft;
    size_t valueWind;
    TypeWind typeWind;

 public:
    TurnDTO();

    TurnDTO(const size_t& idPlayerCurrent, const std::string& textTurn,
            const size_t& timeLeft, const size_t &valueWind, const TypeWind& typeWind);

    size_t getIdPlayerCurrent() const;

    void setIdPlayerCurrent(const size_t &idPlayerCurrent);

    std::string getTextTurn() const;

    void setTextTurn(const std::string &textTurn);

    size_t getTimeLeft() const;

    void setTimeLeft(const size_t &timeLeft);

    size_t getValueWind() const;

    void setValueWind(const size_t &valueWind);

    TypeWind getTypeWind() const;

    void setTypeWind(const TypeWind &typeWind);

    bool operator==(const TurnDTO& other) const;
};


#endif  // WORMS_TALLER_1_TURNDTO_H
