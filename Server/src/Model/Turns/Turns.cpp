//
// Created by abraham on 15/11/23.
//

#include <iostream>
#include "Turns.h"
#include "../../../../Common/DTO/TurnDTO.h"

Turns::Turns(Players &players, const GameParameters &parameters, b2World *world)
        : gameParameters(parameters), players(players), timeLeft(parameters.getTimeForTurn()), damageRecognized(false), attackRecognized(false), valueWind(0.0f), world(world) {
}

float Turns::getWindValueForPhysics(){
    valueWind = (rand() % 99) + 2;  // genero numeros aleatorios del 2 hasta el 100 .  rand %99 me genera numeros entre 0 y el 98 y le sumo 2 -> 2 y 100
    int randomNumber = rand() % 101;
    if(randomNumber % 2 == 0 ){
        typeWind = WIND_RIGHT;
    } else {
        typeWind = WIND_LEFT;
    }
    float aWindValue = static_cast<float>(valueWind) / 10.0f;
    if(typeWind == WIND_LEFT){
        aWindValue *=-1;
    }
    return aWindValue;
}

void Turns::addProvisionToWorld(){
    int randomNumber = rand() % 3; // obtengo numeros random entre 0 y el 2.
    TypeEffect typeEffect = MUNITIONS;
    if(randomNumber == 1){
        typeEffect = MEDICAL_KIT;
    } else if (randomNumber == 2 ){
        typeEffect = EXPLOSION;
    }
    float posXRandom = (float)  ((rand() % 17) +8); // numero random entre  0 y 16 -> +8 -> 8 y 24m
    provisionBoxes.push_back(std::make_unique<Provision>(posXRandom, gameParameters.getPositionYForBoxes(), typeEffect, gameParameters));
    std::cout << "Se lanza provision en: " << posXRandom << ", " << gameParameters.getPositionYForBoxes() << " ) \n";
    provisionBoxes.back()->addToTheWorld(world);
}

void Turns::startATurn() {
    this->addProvisionToWorld();
    this->idPlayerCurrent = players.startAPlayerTurn();
    players.getCurrentPlayer().assignWindValue(getWindValueForPhysics());
    this->idWormCurrent = players.getCurrentPlayer().startAWormTurn();
    this->textTurn = players.getCurrentPlayer().getPlayerName();
    damageRecognized = false;
    attackRecognized = false;
    std::cout << " [New Turn] Id Player actual:" << idPlayerCurrent << "\n";
    std::cout << "Id Current worm: :" << idWormCurrent << "\n";
    std::cout << "Value Wind " << valueWind/10.0f << " Direction: " << typeWind << "\n";
}

int Turns::getTimeLeft() const{
    return this->timeLeft;
}

void Turns::subtractTime() {
    if( timeLeft >= 1){
        timeLeft -=1;
    }
}

void Turns::cleanProvisionsDestroyed(){
    provisionBoxes.erase(std::remove_if(provisionBoxes.begin(), provisionBoxes.end(),
        [this]( std::unique_ptr<Provision>& aProvison) {
        if(aProvison->isDestroyedBody()){
            world->DestroyBody(aProvison->getBody());
            return true;
        }
        return false;
    }) ,provisionBoxes.end());

}


void Turns::tryEndTurn(){
    this->cleanProvisionsDestroyed();
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
    return TurnDTO(idPlayerCurrent, textTurn, timeLeft, valueWind, typeWind);
}

std::vector<ProvisionDTO> Turns::getVecProvisionDTO() {
    std::vector<ProvisionDTO> vecProvisions;
    for(auto& aProvision : provisionBoxes ){
        if(not aProvision->isDestroyedBody()){
            vecProvisions.push_back(aProvision->getProvisionDTO());
        }
    }
    return vecProvisions;
}

