//
// Created by abraham on 06/11/23.
//

#include "SnapShot.h"
//  @todo cuando haya tiempo eliminar este metodo de snapShot.
SnapShot::SnapShot() : DTO(SNAP_SHOT) {

}

SnapShot::SnapShot(const std::vector<WormDTO> &wormsDTO, const PlayersDTO &aPlayersDTO,
                   const WeaponsDTO& weaponsDTO, const WeaponSightDTO &weaponSightDTO, const ProjectilesDTO &projectilesDTO) : DTO(SNAP_SHOT),
            wormsDTO(wormsDTO), playersDTO(aPlayersDTO), weaponsDTO(weaponsDTO), weaponSightDTO(weaponSightDTO), projectilesDTO(projectilesDTO){
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

const WeaponSightDTO &SnapShot::getWeaponSightDto() const {
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



