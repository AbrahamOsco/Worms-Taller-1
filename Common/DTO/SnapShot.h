//
// Created by abraham on 06/11/23.
//

#ifndef WORMS_TALLER_1_SNAPSHOT_H
#define WORMS_TALLER_1_SNAPSHOT_H


#include <vector>
#include "WormDTO.h"
#include "PlayersDTO.h"
#include "WeaponsDTO.h"

class SnapShot : public DTO {
private:
    std::vector<WormDTO> wormsDTO;
    PlayersDTO playersDTO;
    WeaponsDTO weaponsDTO;
public:
    SnapShot();

    explicit SnapShot(const std::vector<WormDTO>& wormsDTO, const PlayersDTO &aPlayersDTO, const WeaponsDTO& weaponsDTO);

    void setWormsDTO(const std::vector<WormDTO>& wormsDTO);

    std::vector<WormDTO> getWormsDto() const;

    PlayersDTO getPlayersDto() const;

    WeaponsDTO getWeaponsDto() const;

    void setPlayersDto(const PlayersDTO &playersDto);

    void setWeaponsDto(const WeaponsDTO &weaponsDto);

};


#endif //WORMS_TALLER_1_SNAPSHOT_H
