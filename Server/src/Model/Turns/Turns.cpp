//
// Created by abraham on 15/11/23.
//

#include <iostream>
#include "Turns.h"
#include "../../../../Common/DTO/TurnDTO.h"
#define TIME_FOR_TURN 10
Turns::Turns(Players &players) : players(players), timeLeft(TIME_FOR_TURN), damageRecognized(false), attackRecognized(false) {
}

void Turns::startATurn() {
    this->idPlayerCurrent = players.startAPlayerTurn();
    this->idWormCurrent = players.getCurrentPlayer().startAWormTurn();
    this->textTurn = players.getCurrentPlayer().getPlayerName();
    damageRecognized = false;
    attackRecognized = false;
    std::cout << "Id Player actual:" << idPlayerCurrent << "\n";
    std::cout << "Id Current worm: :" << idWormCurrent << "\n";

}
int Turns::getTimeLeft() const{
    return this->timeLeft;
}

void Turns::subtractTime() {
    if( timeLeft >= 1){
        timeLeft -=1;
    }
    std::cout << "Time left " << timeLeft << "\n";
}

void Turns::tryEndTurn(){
    // Lo mas facil pasaron 60 segundos entonces.  pasa el turno del sgt jugador.
    if(players.getCurrentPlayer().getCurrentWorm()->wasDamaged() and not damageRecognized ){
        timeLeft = 0;
        damageRecognized = true;
    } else if (players.getCurrentPlayer().getCurrentWorm()->alreadyAttack() and not attackRecognized){
        if(timeLeft > 3){
            timeLeft = 3;
        }
        attackRecognized = true;
    }else if(timeLeft <= 0 and players.allWormsAreUnmoveAndNotExistsProjectiles() ){
        timeLeft = TIME_FOR_TURN;
        players.getCurrentPlayer().endTurn();
        startATurn();
    }
}

TurnDTO Turns::getTurnDTO() const {
    return TurnDTO(idPlayerCurrent, textTurn, timeLeft);
}




