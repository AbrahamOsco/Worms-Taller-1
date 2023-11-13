//
// Created by abraham on 06/11/23.
//

#ifndef WORMS_TALLER_1_SNAPSHOT_H
#define WORMS_TALLER_1_SNAPSHOT_H


#include <vector>
#include "WormDTO.h"
#include "PlayersDTO.h"
#include "WeaponsDTO.h"
#include "WeaponSightDTO.h"

class SnapShot : public DTO {
private:
    std::vector<WormDTO> wormsDTO;
    PlayersDTO playersDTO;
    WeaponsDTO weaponsDTO;
    WeaponSightDTO weaponSightDTO;
public:
    SnapShot();

    explicit SnapShot(const std::vector<WormDTO>& wormsDTO, const PlayersDTO &aPlayersDTO, const WeaponsDTO& weaponsDTO, const WeaponSightDTO &weaponSightDTO );

    void setWormsDTO(const std::vector<WormDTO>& wormsDTO);

    std::vector<WormDTO> getWormsDto() const;

    PlayersDTO getPlayersDto() const;

    WeaponsDTO getWeaponsDto() const;

    void setPlayersDto(const PlayersDTO &playersDto);

    void setWeaponsDto(const WeaponsDTO &weaponsDto);

    const WeaponSightDTO &getWeaponSightDto() const;

    void setWeaponSightDto(const WeaponSightDTO &weaponSightDto);

};


#endif //WORMS_TALLER_1_SNAPSHOT_H
