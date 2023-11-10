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
    std::vector<WeaponDTO> weapons;
    size_t idPlayer;
public:
    WeaponsDTO();

    WeaponsDTO(const std::vector<WeaponDTO>& aWeapons, const size_t& idPlayer);

    std::vector<WeaponDTO> getWeapons() const;

    size_t getIdPlayer() const;

    void setWeapons(const std::vector<WeaponDTO> &weapons);

    void setIdPlayer(const size_t &idPlayer);

};


#endif //WORMS_TALLER_1_WEAPONSDTO_H
