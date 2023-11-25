//
// Created by abraham on 26/10/23.
//

#include <iostream>
#include "Player.h"
#include "../../../GameParameters/GameParameters.h"


Player::Player(const std::string &playerName, const size_t &idPlayer, const GameParameters& gameParameters) : playerName(playerName),
                idPlayer(idPlayer), idCurrentWorm(VALUE_INITIAL), gameParameters(gameParameters), armament(idPlayer, gameParameters){
}
bool Player::lostAllWorms(){
    size_t lostWorms = 0;
    for(auto& aElement: worms){
        if(aElement.second->wasDestroyedWorm()){
            lostWorms++;
        }
    }
   return (lostWorms == this->worms.size());
}

std::vector<WormDTO> Player::getWormsDTO() const {
    std::vector<WormDTO> vecWormsDTO;
    for(auto& aWormElem: worms){
        if(not aWormElem.second->wasDestroyedWorm()){       //  Pusheamos los worms que NO fueron destruidos.
            vecWormsDTO.push_back(aWormElem.second->getWormDTO());
        }
    }
    return vecWormsDTO;
}

void Player::assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm) {
    worms.emplace(idWorm, std::make_unique<Worm>(idWorm, idPlayer, positionInitialWorm.first, positionInitialWorm.second, gameParameters, armament)) ;
}

void Player::assignBonusLife() {
    for(auto& pair : worms){
        pair.second->assignBonusLife();
    }
}

void Player::addToTheWorld(b2World *world) {
    for(auto& aWorm : worms){
        aWorm.second->addToTheWorld(world);
    }
}

size_t Player::startAWormTurn() {
    if( idCurrentWorm == VALUE_INITIAL){
        wormIterator = worms.begin();
        this->idCurrentWorm = wormIterator->first;
        worms[idCurrentWorm]->activateFocus();
        return idCurrentWorm;
    }
    while( wormIterator != worms.end() ){
        wormIterator++;
        if(wormIterator == worms.end()){
            wormIterator = worms.begin();
        }
        if( not worms.at(wormIterator->first)->wasDestroyedWorm() ){
            break;
        }
    }
    this->idCurrentWorm = wormIterator->first;
    worms[idCurrentWorm]->activateFocus();
    return this->idCurrentWorm;
}

void Player::update() {
    for(auto& pair : worms){
        pair.second->update();
    }
}

PlayerDTO Player::getPlayerDTO(const size_t &idCurrentPlayer) const {
    TurnType aTurnType = TurnType::NOT_IS_MY_TURN;
    if(this->idPlayer == idCurrentPlayer ){
        aTurnType = TurnType::MY_TURN;
    }
    size_t hpTotalWorms = 0;
    for(auto& mapWorm : worms ){
        if(not mapWorm.second->wasDestroyedWorm()){
            hpTotalWorms += mapWorm.second->getHP();
        }
    }
    return PlayerDTO(idPlayer, playerName, aTurnType, hpTotalWorms);
}

WeaponsDTO Player::getWeaponsDTO() const {
    return armament.getWeaponsDTO();
}

Worm * Player::getCurrentWorm() {
    return worms.at(idCurrentWorm).get();
}

std::string Player::getPlayerName() const {
    return this->playerName;
}

void Player::endTurn() {
    this->worms.at(idCurrentWorm)->endTurn();
}

bool Player::allWormsAreUnmoveAndNotExistsProjectiles() {
    for (auto &aWorm: worms) {
        if (not aWorm.second->isUnmoveAndNotExistsPojectiles()) {
            return false;
        }
    }
    return true;
}

void Player::execute(std::unique_ptr<CommandDTO> &uniquePtr, const int &timeLeft) {
    if(uniquePtr->getTypeCommand() == COUNTDOWN){
        for(auto &aWorms : worms){
            aWorms.second->setWaitTime(uniquePtr->getX());
        }
        return;
    }
    this->worms.at(idCurrentWorm)->execute(uniquePtr, timeLeft, idCurrentWorm);

}

void Player::assignWindValue(const float &aWindValue) {
    this->armament.assignWindValue(aWindValue);
}

EndGameDTO Player::getEndGameDTO() {
    if(this->lostAllWorms()){
        return EndGameDTO(this->idPlayer, LOST_THE_GAME);
    }
    return EndGameDTO(this->idPlayer, WON_THE_GAME);
}

void Player::setLifeAllWorm(const float &aNewHP) {
    for(auto& aWorm : worms){
        if(not aWorm.second->wasDestroyedWorm()){
            aWorm.second->setHP(aNewHP);
        }
    }
}

void Player::getMovingWorms(std::vector<std::pair<size_t, size_t>>& idPlayerAndWorm){
    for(auto& aWorm : worms){
        if( not aWorm.second->wasDestroyedWorm() and  not aWorm.second->isStopTheWorm()){
            idPlayerAndWorm.emplace_back(this->idPlayer, aWorm.first);
        }
    }

}

std::unique_ptr<Worm> * Player::getWorm(const size_t &idWorm) {
    return &worms.at(idWorm);
}

void Player::disableAllFocus() {
    for(auto& aWorm: worms){
        if(not aWorm.second->wasDestroyedWorm()){
            aWorm.second->assignTypeFocus(NO_FOCUS);
        }
    }
}
