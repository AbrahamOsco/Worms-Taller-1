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

enum GameState{
    GAME_PROGRESS, GAME_END
};


class SnapShot : public DTO {
private:
    GameState typeSnapShot;
    std::vector<WormDTO> wormsDTO;
    PlayersDTO playersDTO;
    WeaponsDTO weaponsDTO;
    WeaponSightDTO weaponSightDTO;
    ProjectilesDTO projectilesDTO;
    TurnDTO turnDto;
    EndGameDTO endGameDTO;
public:

    explicit SnapShot(const EndGameDTO& endGameDTO);

    explicit SnapShot(const std::vector<WormDTO>& wormsDTO, const PlayersDTO &aPlayersDTO, const WeaponsDTO& weaponsDTO,
                      const WeaponSightDTO &weaponSightDTO, const ProjectilesDTO &projectilesDTO, const TurnDTO& turnDto );

    void setWormsDTO(const std::vector<WormDTO>& wormsDTO);

    std::vector<WormDTO> getWormsDto() const;

    PlayersDTO getPlayersDto() const;

    WeaponsDTO getWeaponsDto() const;

    void setPlayersDto(const PlayersDTO &playersDto);

    void setWeaponsDto(const WeaponsDTO &weaponsDto);

    WeaponSightDTO getWeaponSightDto() const;

    void setWeaponSightDto(const WeaponSightDTO &weaponSightDto);

    ProjectilesDTO getProjectilesDto() const;

    void setProjectilesDto(const ProjectilesDTO &projectilesDto);

    TurnDTO getTurnDto() const;

    void setTurnDto(const TurnDTO &turnDto);

    GameState getTypeSnapShot() const;

    EndGameDTO getEndGameDto() const;
};


#endif //WORMS_TALLER_1_SNAPSHOT_H
