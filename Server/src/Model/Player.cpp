//
// Created by abraham on 26/10/23.
//

#include "Player.h"
#include "../../ConfigureParameters/ConfigParameters.h"


Player::Player() : idCurrentWorm(VALUE_INITIAL) {
}

Player::Player(const std::string &playerName, const size_t &idPlayer) : playerName(playerName), idPlayer(idPlayer), idCurrentWorm(VALUE_INITIAL) {
}

std::vector<WormDTO> Player::getWormsDTO() const {
    std::vector<WormDTO> vecWormsDTO;
    for(auto& aWormElem: worms){
        WormDTO aWormDTO = WormDTO(aWormElem.second->getPositionX() * POSITION_ADJUSTMENT, aWormElem.second->getPositionY() * POSITION_ADJUSTMENT, aWormElem.second->getHP(),
                                   aWormElem.second->getDirectionLook(), aWormElem.second->getTypeFocusWorm(), aWormElem.second->getTypeMov());
        vecWormsDTO.push_back(aWormDTO);
    }
    return vecWormsDTO;
}

void Player::assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm) {
    // agregamos al diccionario la calve el id de worm y el valor el worm con su position inicial en x,y.
    worms.emplace(idWorm, std::make_unique<Worm>(idWorm, positionInitialWorm.first, positionInitialWorm.second)) ;
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
