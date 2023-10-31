//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H

#include <string>
#include <vector>
#include "Worm.h"
#include "../../../Common/DTO/PlayerDTO.h"

class Player {
private:

    std::string playerName;
    size_t idPlayer;
    size_t wormCurrentPosition;
    std::vector<Worm> worms;

public:
    Player();

    Player(const std::string& playerName, const size_t& idPlayer);

    PlayerDTO getPlayerDTO() const;

};


#endif //WORMS_TALLER_1_PLAYER_H
