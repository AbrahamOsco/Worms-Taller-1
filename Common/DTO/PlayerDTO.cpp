//
// Created by abraham on 31/10/23.
//

#include "PlayerDTO.h"

PlayerDTO::PlayerDTO() : DTO(PLAYER) {
}

size_t PlayerDTO::getIdPlayer() const {
    return idPlayer;
}

PlayerDTO::PlayerDTO(const size_t &idPlayer, const std::vector<WormDTO> &worms) : DTO(PLAYER), idPlayer(idPlayer), wormsBelongToPlayer(worms) {

}

std::vector<WormDTO> PlayerDTO::getWorms() const {
    return this->wormsBelongToPlayer;
}




