//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <box2d/b2_world.h>
#include <memory>
#include "Worm.h"
#include "../../../Common/DTO/PlayerDTO.h"
#define VALUE_INITIAL 1000

class Player {
private:
    std::string playerName;
    size_t idPlayer;
    std::map<size_t, std::unique_ptr<Worm>> worms;
    std::map<size_t, std::unique_ptr<Worm>>::iterator wormIterator;
    size_t idCurrentWorm;
public:
    Player();

    Player(const std::string& playerName, const size_t& idPlayer);

    std::vector<WormDTO> getWormsDTO() const;

    size_t getCurrentWormId();

    void assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm);

    void assignBonusLife();

    void addToTheWorld(b2World *world);

    void leftWorm();

    void rightWorm();
};


#endif //WORMS_TALLER_1_PLAYER_H
