//
// Created by abraham on 15/11/23.
//

#ifndef WORMS_TALLER_1_TURNS_H
#define WORMS_TALLER_1_TURNS_H


#include "../Players/Players.h"
#include "../../../../Common/DTO/TurnDTO.h"

class Turns {
private:
    GameParameters gameParameters;
    Players& players;
    size_t idPlayerCurrent;
    std::string textTurn;
    int timeLeft;
    size_t idWormCurrent;
    bool damageRecognized;
    bool attackRecognized;
    int valueWind; // valor del viento multiplicado por 10  ej si valueWind= 100-> valorVientoReal = 10.
    TypeWind typeWind;
public:

    explicit Turns(Players &players, const GameParameters& parameters);

    void startATurn();


    void subtractTime();

    void tryEndTurn();

    TurnDTO getTurnDTO() const;

    int getTimeLeft() const;

    float getWindValueForPhysics();
};


#endif //WORMS_TALLER_1_TURNS_H
