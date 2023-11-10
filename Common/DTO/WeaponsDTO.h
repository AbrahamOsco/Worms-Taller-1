//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONSDTO_H
#define WORMS_TALLER_1_WEAPONSDTO_H


#include <vector>
#include "DTO.h"
#include "WeaponDTO.h"

class WeaponsDTO : public DTO {
private:
    size_t idPlayer;
    std::vector<WeaponDTO> weapons;
public:
    WeaponsDTO();

    WeaponsDTO(const size_t &idPlayer, const std::vector<WeaponDTO> &aWeapons);

    std::vector<WeaponDTO> getWeapons() const;

    size_t getIdPlayer() const;

    void setWeapons(const std::vector<WeaponDTO> &weapons);

    void setIdPlayer(const size_t &idPlayer);

};


#endif //WORMS_TALLER_1_WEAPONSDTO_H
