//
// Created by abraham on 15/11/23.
//

#include <iostream>
#include "Turns.h"
#include "../../../../Common/DTO/TurnDTO.h"
Turns::Turns(Players &players, const GameParameters& parameters)
        : gameParameters(parameters), players(players), timeLeft(parameters.getTimeForTurn()), damageRecognized(false), attackRecognized(false) {
}

void Turns::startATurn() {
    this->idPlayerCurrent = players.startAPlayerTurn();
    this->idWormCurrent = players.getCurrentPlayer().startAWormTurn();
    this->textTurn = players.getCurrentPlayer().getPlayerName();
    damageRecognized = false;
    attackRecognized = false;
    std::cout << " [New Turn] Id Player actual:" << idPlayerCurrent << "\n";
    std::cout << "Id Current worm: :" << idWormCurrent << "\n";

}
int Turns::getTimeLeft() const{
    return this->timeLeft;
}

void Turns::subtractTime() {
    if( timeLeft >= 1){
        timeLeft -=1;
    }
}

void Turns::tryEndTurn(){
    // Lo mas facil pasaron 60 segundos entonces.  pasa el turno del sgt jugador.
    if (players.getCurrentPlayer().getCurrentWorm()->wasDamaged() and not damageRecognized) {
        timeLeft = 0;
        damageRecognized = true;
    } else if (players.getCurrentPlayer().getCurrentWorm()->alreadyAttack() and not attackRecognized) {
        if (timeLeft > gameParameters.getTimeExtraAfterAttack()) {
            timeLeft = gameParameters.getTimeExtraAfterAttack();
        }
        attackRecognized = true;
    } else if (timeLeft <= 0 and players.allWormsAreUnmoveAndNotExistsProjectiles()) { // solo acabara el turno cuando todos los worms estan quietos y no existan projectiles
        timeLeft = gameParameters.getTimeForTurn();
        players.getCurrentPlayer().endTurn();
        startATurn();
    }
}

TurnDTO Turns::getTurnDTO() const {
    return TurnDTO(idPlayerCurrent, textTurn, timeLeft);
}




