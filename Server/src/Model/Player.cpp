//
// Created by abraham on 26/10/23.
//

#include "Player.h"

Player::Player() {
}


Player::Player(const std::string &playerName, const size_t &idPlayer) : playerName(playerName), idPlayer(idPlayer) {
}

PlayerDTO Player::getPlayerDTO() const {
    std::vector<WormDTO> vecWorms;
    for(auto& aWorm: worms){
        vecWorms.push_back( aWorm.second.getWormInitialDTO() );
    }
    return PlayerDTO(idPlayer, vecWorms);
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

