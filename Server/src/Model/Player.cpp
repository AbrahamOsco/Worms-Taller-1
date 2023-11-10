//
// Created by abraham on 26/10/23.
//

#include "Player.h"
#include "../../GameParameters//GameParameters.h"



Player::Player(const std::string &playerName, const size_t &idPlayer, const GameParameters& gameParameters) : playerName(playerName),
                idPlayer(idPlayer), idCurrentWorm(VALUE_INITIAL), gameParameters(gameParameters), armament(idPlayer) {
}

// Aca Falta hacer gameParameters.getMaxHeightPixel() - (aWormElem.second->getPositionY() * gameParameters.getPositionAdjustment())  para la posicion en Y.

std::vector<WormDTO> Player::getWormsDTO() const {
    std::vector<WormDTO> vecWormsDTO;
    for(auto& aWormElem: worms){
        WormDTO aWormDTO = WormDTO(aWormElem.second->getPositionX() * gameParameters.getPositionAdjustment(),
                                   aWormElem.second->getPositionY() * gameParameters.getPositionAdjustment(), aWormElem.second->getHP(),
                                   aWormElem.second->getDirectionLook(), aWormElem.second->getTypeFocusWorm(), aWormElem.second->getTypeMov());
        vecWormsDTO.push_back(aWormDTO);
    }
    return vecWormsDTO;
}

void Player::assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm) {
    // agregamos al diccionario la calve el id de worm y el valor el worm con su position inicial en x,y.
    worms.emplace(idWorm, std::make_unique<Worm>(idWorm, positionInitialWorm.first, positionInitialWorm.second, gameParameters, armament)) ;
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

size_t Player::getCurrentWormId() {
    if( idCurrentWorm == VALUE_INITIAL){
        wormIterator = worms.begin();
        this->idCurrentWorm = wormIterator->first;
        worms[idCurrentWorm]->activateFocus();
        return idCurrentWorm;
    }
    wormIterator++; // avanzamos al iterador.
    if (wormIterator == worms.end()){
        wormIterator == worms.begin();
    }
    this->idCurrentWorm = wormIterator->first;
    worms[idCurrentWorm]->activateFocus();
    return this->idCurrentWorm;
}

void Player::leftWorm() {
    this->worms[idCurrentWorm]->leftWorm();
}

void Player::rightWorm() {
    this->worms[idCurrentWorm]->rightWorm();
}

void Player::jumpBackWorm() {
    this->worms[idCurrentWorm]->jumpBackwards();
}

void Player::jumpForwardWorm() {
    this->worms[idCurrentWorm]->jumpForwards();
}

void Player::updateStateWorms() {
    for(auto& pair : worms){
        pair.second->stopIfUnmoving();
    }
}

PlayerDTO Player::getPlayerDTO(const size_t &idCurrentPlayer) const {
    TurnType aTurnType = TurnType::NOT_IS_MY_TURN;
    if(this->idPlayer == idCurrentPlayer ){
        aTurnType = TurnType::MY_TURN;
    }
    size_t hpTotalWorms = 0;
    for(auto& mapWorm : worms ){
        hpTotalWorms += mapWorm.second->getHP();
    }
    return PlayerDTO(idPlayer, playerName, aTurnType, hpTotalWorms);
}

WeaponsDTO Player::getWeaponsDTO() const {
    return armament.getWeaponsDTO();
}


