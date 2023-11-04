//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <box2d/b2_world.h>
#include "Worm.h"
#include "../../../Common/DTO/PlayerDTO.h"

class Player {
private:
    std::string playerName;
    size_t idPlayer;
    std::map<size_t, Worm> worms;
public:
    Player();

    Player(const std::string& playerName, const size_t& idPlayer);

    PlayerDTO getPlayerDTO() const;

    void assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm);

    void assignBonusLife();

    void addToTheWorld(b2World *world);
};


#endif //WORMS_TALLER_1_PLAYER_H
