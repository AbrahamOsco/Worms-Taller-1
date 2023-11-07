//
// Created by abraham on 31/10/23.
//

#ifndef WORMS_TALLER_1_PLAYERDTO_H
#define WORMS_TALLER_1_PLAYERDTO_H


#include <cstddef>
#include <vector>
#include "DTO.h"
#include "WormDTO.h"


class PlayerDTO : public DTO {
private:
    size_t idPlayer;
    std::vector<WormDTO> wormsBelongToPlayer;
public:
    PlayerDTO();

    PlayerDTO(const size_t& idPlayer, const std::vector<WormDTO>& worms);

    size_t getIdPlayer() const;

    std::vector<WormDTO> getWorms() const;
};


#endif //WORMS_TALLER_1_PLAYERDTO_H
