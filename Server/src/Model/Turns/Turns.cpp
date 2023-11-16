//
// Created by abraham on 15/11/23.
//

#include <iostream>
#include "Turns.h"
#include "../../../../Common/DTO/TurnDTO.h"

Turns::Turns(Players &players) : players(players) {
    timeLeft = 15;
}

void Turns::startATurn() {
    this->idPlayerCurrent = players.startAPlayerTurn();
    this->idWormCurrent = players.getCurrentPlayer().startAWormTurn();
    this->textTurn = players.getCurrentPlayer().getPlayerName();
    std::cout << "Id del jugador actual es " << idPlayerCurrent << "\n";
    std::cout << "Id del worm actual es " << idWormCurrent << "\n";
}

void Turns::subtractTime() {
    timeLeft --;
    std::cout << "Time left " << timeLeft << "\n";
}

void Turns::tryEndTurn(){
    // Lo mas facil pasaron 60 segundos entonces.  pasa el turno del sgt jugador.
    if(timeLeft <= 0){
        timeLeft = 15;
        players.getCurrentPlayer().endTurn();
        startATurn();
    }
}

TurnDTO Turns::getTurnDTO() const {
    return TurnDTO(idPlayerCurrent, textTurn, timeLeft);
}



