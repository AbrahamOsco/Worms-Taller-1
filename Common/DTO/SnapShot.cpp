//
// Created by abraham on 06/11/23.
//

#include "SnapShot.h"

SnapShot::SnapShot(const EndGameDTO &aEndGameDTO) : DTO(SNAP_SHOT) , typeSnapShot(GAME_END), endGameDTO(aEndGameDTO) {

}


SnapShot::SnapShot(const std::vector<WormDTO> &wormsDTO, const PlayersDTO &aPlayersDTO, const WeaponsDTO& weaponsDTO, const WeaponSightDTO &weaponSightDTO,
                   const ProjectilesDTO &projectilesDTO, const TurnDTO& turnDto, const std::vector<ProvisionDTO> &vecProvisionDTO) : DTO(SNAP_SHOT),
            typeSnapShot(GAME_PROGRESS), wormsDTO(wormsDTO), playersDTO(aPlayersDTO), weaponsDTO(weaponsDTO),
            weaponSightDTO(weaponSightDTO), projectilesDTO(projectilesDTO),turnDto(turnDto), vecProvisionDTO(vecProvisionDTO) {
}


void SnapShot::setWormsDTO(const std::vector<WormDTO> &wormsDTO) {
    this->wormsDTO = wormsDTO;
}

std::vector<WormDTO> SnapShot::getWormsDto() const {
    return wormsDTO;
}

PlayersDTO SnapShot::getPlayersDto() const {
    return playersDTO;
}

void SnapShot::setPlayersDto(const PlayersDTO &playersDto) {
    this->playersDTO = playersDto;
}

WeaponsDTO SnapShot::getWeaponsDto() const {
    return weaponsDTO;
}

void SnapShot::setWeaponsDto(const WeaponsDTO &weaponsDto) {
    this->weaponsDTO = weaponsDto;
}

WeaponSightDTO SnapShot::getWeaponSightDto() const {
    return weaponSightDTO;
}

void SnapShot::setWeaponSightDto(const WeaponSightDTO &weaponSightDto) {
    this->weaponSightDTO = weaponSightDto;
}

ProjectilesDTO SnapShot::getProjectilesDto() const {
    return projectilesDTO;
}

void SnapShot::setProjectilesDto(const ProjectilesDTO &projectilesDto) {
    projectilesDTO = projectilesDto;
}

TurnDTO SnapShot::getTurnDto() const {
    return turnDto;
}

void SnapShot::setTurnDto(const TurnDTO &turnDto) {
    this->turnDto = turnDto;
}

GameState SnapShot::getTypeSnapShot() const {
    return typeSnapShot;
}

EndGameDTO SnapShot::getEndGameDto() const {
    return this->endGameDTO;
}

std::vector<ProvisionDTO> SnapShot::getVecProvisionDto() const {
    return vecProvisionDTO;
}
