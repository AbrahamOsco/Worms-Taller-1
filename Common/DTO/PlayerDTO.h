//
// Created by abraham on 31/10/23.
//

#ifndef WORMS_TALLER_1_PLAYERDTO_H
#define WORMS_TALLER_1_PLAYERDTO_H


#include <cstddef>
#include <vector>
#include <string>
#include "DTO.h"

enum TurnType{
    MY_TURN, NOT_IS_MY_TURN
};

class PlayerDTO : public DTO {
private:
    size_t idPlayer;
    std::string namePlayer;
    TurnType turnType;
    size_t totalHPWorms;
public:
    PlayerDTO();

    PlayerDTO(const size_t& idPlayer, const std::string& aNamePlayer, const TurnType& aTurnType, const size_t& aTotalHPWorms);


    size_t getIdPlayer() const;

    TurnType getTurnType() const;

    std::string getNamePlayer() const;

    size_t getTotalHpWorms() const;

    void setIdPlayer(const size_t &idPlayer);

    void setNamePlayer(const std::string &namePlayer);

    void setTurnType(const TurnType &turnType);

    void setTotalHpWorms(const size_t &totalHpWorms);

};


#endif //WORMS_TALLER_1_PLAYERDTO_H
