//
// Created by abraham on 31/10/23.
//

#include "Players.h"

Players::Players() {

}

void Players::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players[idPlayer] = Player(playerName, idPlayer);
}

std::vector<PlayerDTO> Players::getPlayersDTO() const {
    std::vector<PlayerDTO> playersDTO;
    for(auto it = players.begin();  it != players.end(); it++){
        playersDTO.push_back(it->second.getPlayerDTO());
    }
    return playersDTO;
}
