//
// Created by abraham on 02/11/23.
//

#ifndef WORMS_TALLER_1_PLAYERSINIDTO_H
#define WORMS_TALLER_1_PLAYERSINIDTO_H


#include "PlayerDTO.h"

class PlayersIniDTO : public DTO {
private:
    std::vector<PlayerDTO> playersDTO;

public:
    PlayersIniDTO();

    PlayersIniDTO(const std::vector<PlayerDTO>& aPlayersDTO);

    std::vector<PlayerDTO> getPlayersIniDTO() const;

    void setPlayersIniDTO(const std::vector<PlayerDTO>& aPlayersDTO);


};


#endif //WORMS_TALLER_1_PLAYERSINIDTO_H
