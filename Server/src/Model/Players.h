//
// Created by abraham on 31/10/23.
//

#ifndef WORMS_TALLER_1_PLAYERS_H
#define WORMS_TALLER_1_PLAYERS_H


#include <map>
#include <vector>
#include <box2d/b2_world.h>
#include "Player.h"
#include "../../../Common/DTO/PlayerDTO.h"

class Players {
private:
    std::map<size_t, std::pair<float, float>> idsAndPositionsWorms;
    std::map<size_t, Player> players;
    size_t idCurrenPlayer;
    std::map<size_t, Player>::iterator playerIterator;


public:
    explicit Players(const std::map<size_t, std::pair<float, float>>& idsAndPositionsWorms);

    void addPlayer(const std::string &playerName, const size_t &idPlayer);

    void assignWormsToPlayers();

    std::vector<WormDTO> getWormsDTO() const;

    size_t getCurrentPlayerId();

    void addToTheWorld(b2World *world);
};


#endif //WORMS_TALLER_1_PLAYERS_H
