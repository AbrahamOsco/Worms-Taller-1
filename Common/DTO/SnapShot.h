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
#include "ProjectilesDTO.h"
#include "TurnDTO.h"
#include "EndGameDTO.h"

enum TypeSnapShot{
    GAME_PROGRESS, GAME_END
};


class SnapShot : public DTO {
private:
    TypeSnapShot typeSnapShot;
private:
    std::vector<WormDTO> wormsDTO;
    PlayersDTO playersDTO;
    WeaponsDTO weaponsDTO;
    WeaponSightDTO weaponSightDTO;
    ProjectilesDTO projectilesDTO;
    TurnDTO turnDto;
    std::vector<EndGameDTO> vecEndGamesDTO;
public:
    std::vector<EndGameDTO> getVecEndGamesDto() const;

public:

    explicit SnapShot(const std::vector<EndGameDTO>& vecEndGameDTO);

    explicit SnapShot(const std::vector<WormDTO>& wormsDTO, const PlayersDTO &aPlayersDTO, const WeaponsDTO& weaponsDTO,
                      const WeaponSightDTO &weaponSightDTO, const ProjectilesDTO &projectilesDTO, const TurnDTO& turnDto );

    void setWormsDTO(const std::vector<WormDTO>& wormsDTO);

    std::vector<WormDTO> getWormsDto() const;

    PlayersDTO getPlayersDto() const;

    WeaponsDTO getWeaponsDto() const;

    void setPlayersDto(const PlayersDTO &playersDto);

    void setWeaponsDto(const WeaponsDTO &weaponsDto);

    const WeaponSightDTO &getWeaponSightDto() const;

    void setWeaponSightDto(const WeaponSightDTO &weaponSightDto);

    ProjectilesDTO getProjectilesDto() const;

    void setProjectilesDto(const ProjectilesDTO &projectilesDto);

    TurnDTO getTurnDto() const;

    void setTurnDto(const TurnDTO &turnDto);

    TypeSnapShot getTypeSnapShot() const;

};


#endif //WORMS_TALLER_1_SNAPSHOT_H
