//
// Created by abraham on 02/11/23.
//

#ifndef WORMS_TALLER_1_PLAYERSDTO_H
#define WORMS_TALLER_1_PLAYERSDTO_H


#include "PlayerDTO.h"
#include <vector>

class PlayersDTO : public DTO {
 private:
    std::vector<PlayerDTO> playersDTO;

 public:
    PlayersDTO();

    explicit PlayersDTO(const std::vector<PlayerDTO>& aPlayersDTO);

    std::vector<PlayerDTO> getPlayersDTO() const;

    void setPlayersIniDTO(const std::vector<PlayerDTO>& aPlayersDTO);

    bool operator==(const PlayersDTO& other) const;
};


#endif  // WORMS_TALLER_1_PLAYERSDTO_H
