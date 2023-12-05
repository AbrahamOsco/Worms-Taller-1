//
// Created by abraham on 15/11/23.
//

#include <iostream>
#include "Turns.h"
#include "../../../../Common/DTO/TurnDTO.h"

#define MAX_VALUE_WIND 5
Turns::Turns(Players &players, const GameParameters &parameters, b2World *world)
        : gameParameters(parameters), players(players), timeLeft(parameters.getTimeForTurn()),
            damageRecognized(false), attackRecognized(false), valueWind(0.0f), world(world),
          focusController(players), idPlayerCurrent(0), idWormCurrent(0), typeWind(WIND_LEFT) {
}

float Turns::getWindValueForPhysics() {
    valueWind = (rand() % (MAX_VALUE_WIND -1) ) + 2;
    int randomNumber = rand() % MAX_VALUE_WIND;
    if (randomNumber % 2 == 0) {
        typeWind = WIND_RIGHT;
    } else {
        typeWind = WIND_LEFT;
    }
    float aWindValue = static_cast<float>(valueWind) / 10.0f;
    if (typeWind == WIND_LEFT) {
        aWindValue *=-1;
    }
    return aWindValue;
}

void Turns::addProvisionToWorld() {
    int randomNumber = rand()  % 3;
    TypeEffect typeEffect = MUNITIONS;
    if (randomNumber == 1) {
        typeEffect = MEDICAL_KIT;
    } else if ( randomNumber == 2 ) {
        typeEffect = EXPLOSION;
    }
    float posXRandom = (float)  ((rand() % 17) +8);
    provisionBoxes.push_back(std::make_unique<Provision>(posXRandom, gameParameters.getPositionYForBoxes(),
        typeEffect, gameParameters));
    provisionBoxes.back()->addToTheWorld(world);
}

void Turns::startATurn() {
    this->addProvisionToWorld();
    this->idPlayerCurrent = players.startAPlayerTurn();
    players.getCurrentPlayer().assignWindValue(getWindValueForPhysics());
    this->idWormCurrent = players.getCurrentPlayer().startAWormTurn();
    focusController.assignPlayerAndWormCurrent(idPlayerCurrent, idWormCurrent);
    this->textTurn = players.getCurrentPlayer().getPlayerName();
    damageRecognized = false;
    attackRecognized = false;
}

void Turns::tryToChangeFocus() {
    focusController.tryToChangeFocus();
}

int Turns::getTimeLeft() const {
    return this->timeLeft;
}

void Turns::subtractTime() {
    if ( timeLeft >= 1 ) {
        timeLeft -= 1;
    }
}

void Turns::cleanProvisionsDestroyed() {
    provisionBoxes.erase(std::remove_if(provisionBoxes.begin(), provisionBoxes.end(),
        [this](std::unique_ptr<Provision>& aProvison) {
        if ( aProvison->isDestroyedBody() && !aProvison->hasIterations() ) {
            world->DestroyBody(aProvison->getBody());
            return true;
        }
        return false;
    }) , provisionBoxes.end());
}


void Turns::tryEndTurn() {
    this->cleanProvisionsDestroyed();
    if ((players.getCurrentPlayer().getCurrentWorm()->wasDamaged() ||
        players.getCurrentPlayer().getCurrentWorm()->wasDestroyedWorm()) && !damageRecognized) {
        timeLeft = 0;
        damageRecognized = true;
    } else if (players.getCurrentPlayer().getCurrentWorm()->alreadyAttack() && !attackRecognized) {
        if (timeLeft > gameParameters.getTimeExtraAfterAttack()) {
            timeLeft = gameParameters.getTimeExtraAfterAttack();
        }
        attackRecognized = true;
    } else if (timeLeft <= 0 && players.allWormsAreUnmoveAndNotExistsProjectiles()) {
        timeLeft = gameParameters.getTimeForTurn();
        players.getCurrentPlayer().endTurn();
        if (!players.onlyExistsOnePlayer()) {
            players.disableAllFocus();
            startATurn();
        }
    }
}

TurnDTO Turns::getTurnDTO() const {
    return TurnDTO(idPlayerCurrent, textTurn, timeLeft, valueWind, typeWind);
}

std::vector<ProvisionDTO> Turns::getVecProvisionDTO() {
    std::vector<ProvisionDTO> vecProvisions;
    for ( auto& aProvision : provisionBoxes ) {
        aProvision->getProvisionDTO(vecProvisions);
    }
    return vecProvisions;
}

