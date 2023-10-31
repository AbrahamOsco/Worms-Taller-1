//
// Created by abraham on 31/10/23.
//

#ifndef WORMS_TALLER_1_PLAYERS_H
#define WORMS_TALLER_1_PLAYERS_H


#include <map>
#include <vector>
#include "Player.h"
#include "../../../Common/DTO/PlayerDTO.h"

class Players {
private:
    size_t idPlayer;
    std::map<size_t, Player> players;

public:
    Players();

    void addPlayer(const std::string &playerName, const size_t &idPlayer);


    std::vector<PlayerDTO> getPlayersDTO() const;
};


#endif //WORMS_TALLER_1_PLAYERS_H
