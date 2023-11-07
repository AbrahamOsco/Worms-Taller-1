//
// Created by abraham on 26/10/23.
//

#include "Player.h"
Player::Player() : idCurrentWorm(VALUE_INITIAL) {
}

Player::Player(const std::string &playerName, const size_t &idPlayer) : playerName(playerName), idPlayer(idPlayer), idCurrentWorm(VALUE_INITIAL) {
}

std::vector<WormDTO> Player::getWormsDTO() const {
    std::vector<WormDTO> vecWormsDTO;
    for(auto& aWormElement: worms){
        Worm aWorm = aWormElement.second;
        WormDTO aWormDTO = WormDTO(aWorm.getPositionX(), aWorm.getPositionY(), aWorm.getHP(), aWorm.getDirectionLook(), aWorm.getTypeFocusWorm(), aWorm.getTypeMov());
        vecWormsDTO.push_back(aWormDTO);
    }
    return vecWormsDTO;
}

void Player::assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm) {
    // agregamos al diccionario la calve el id de worm y el valor el worm con su position inicial en x,y.
    worms.emplace(idWorm, Worm(positionInitialWorm.second, idWorm, positionInitialWorm.first));
}

void Player::assignBonusLife() {
    for(auto& pair : worms){
        pair.second.assignBonusLife();
    }
}

void Player::addToTheWorld(b2World *world) {
    for(auto aWorm : worms){
        aWorm.second.addToTheWorld(world);
    }
}

size_t Player::getCurrentWormId() {
    if( idCurrentWorm == VALUE_INITIAL){
        wormIterator = worms.begin();
        this->idCurrentWorm = wormIterator->first;
        worms[idCurrentWorm].activateFocus();
        return idCurrentWorm;
    }
    wormIterator++; // avanzamos al iterador.
    if (wormIterator == worms.end()){
        wormIterator == worms.begin();
    }
    this->idCurrentWorm = wormIterator->first;
    worms[idCurrentWorm].activateFocus();
    return this->idCurrentWorm;
}

