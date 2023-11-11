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
    TypeWeapon weaponCurrent;
public:
    WeaponsDTO();

    WeaponsDTO(const size_t &idPlayer, const std::vector<WeaponDTO> &aWeapons,const TypeWeapon& weaponCurrent );

    std::vector<WeaponDTO> getWeapons() const;

    size_t getIdPlayer() const;

    TypeWeapon getWeaponCurrent() const;

    void setWeapons(const std::vector<WeaponDTO> &weapons);

    void setIdPlayer(const size_t &idPlayer);

    void setWeaponCurrent(const TypeWeapon &weaponCurrent);

};


#endif //WORMS_TALLER_1_WEAPONSDTO_H
