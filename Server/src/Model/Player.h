//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H

#include <string>

class Player {
private:
    std::string playerName;
    size_t idPlayer;
public:

    Player();
    Player(const std::string& playerName, const size_t& idPlayer);
};


#endif //WORMS_TALLER_1_PLAYER_H
