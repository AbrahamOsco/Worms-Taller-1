//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONDTO_H
#define WORMS_TALLER_1_WEAPONDTO_H

#include <cstddef>
#include "DTO.h"

enum TypeWeapon{
    NONE_WEAPON,
    BAZOOKA,
    MORTAR,
    RED_GRENADE,
    GREEN_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AIR_ATTACK,
    TELEPORTATION
};

enum TypeMunition{
    INFINITE,
    NO_INFINITE
};

class WeaponDTO : public DTO {
private:
    TypeWeapon typeWeapon;
    TypeMunition typeMunition;
    size_t munition;
public:
    WeaponDTO();

    WeaponDTO(const TypeWeapon &aTypeWeapon, const TypeMunition &aTypeMunition, const size_t &aMunition);

    TypeWeapon getTypeWeapon() const;

    TypeMunition getTypeMunition() const;

    size_t getMunition() const;

    void setTypeWeapon(const TypeWeapon &typeWeapon);

    void setATypeMunition(const TypeMunition &aTypeMunition);

    void setMunition(const size_t &munition);

};


#endif //WORMS_TALLER_1_WEAPONDTO_H
