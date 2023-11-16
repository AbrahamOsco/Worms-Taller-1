//
// Created by abraham on 15/11/23.
//

#ifndef WORMS_TALLER_1_TURNS_H
#define WORMS_TALLER_1_TURNS_H


#include "../Players/Players.h"
#include "../../../../Common/DTO/TurnDTO.h"

class Turns {
private:
    Players& players;
    size_t idPlayerCurrent;
    std::string textTurn;
    int timeLeft;
    size_t idWormCurrent;
public:

    explicit Turns(Players& players);

    void startATurn();


    void subtractTime();

    void tryEndTurn();

    TurnDTO getTurnDTO() const;
};


#endif //WORMS_TALLER_1_TURNS_H
