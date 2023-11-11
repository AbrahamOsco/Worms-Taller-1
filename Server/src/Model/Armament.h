//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_ARMAMENT_H
#define WORMS_TALLER_1_ARMAMENT_H


#include <map>
#include <memory>
#include "Weapon.h"
#include "Bat.h"
#include "../../../Common/DTO/WormDTO.h"
#include "../../../Common/DTO/WeaponsDTO.h"

class Armament {
private:
    size_t idPlayer;
    std::map<TypeWeapon, std::unique_ptr<Weapon> > armament; // si no funcionan usaremos unique_ptr en weapon
    TypeWeapon currentWeapon;
    TypeWeapon weaponOnStandBy;

public:
    Armament(const size_t& idPlayer);

    bool hasAWeapon();

    Weapon* getWeapon(const TypeWeapon& aTypeWeapon);

    TypeWeapon getWeaponCurrent() const;

    bool isUnarmed() const;

    bool hasAScoped();

    void changeDirection(const Direction &direction);

    void unarmed();

    void putWeaponOnStandBy();

    void getWeaponOnStandBy();

    void assignWeapon(const TypeWeapon &weapon, const Direction &direction);

    WeaponsDTO getWeaponsDTO() const;
};


#endif //WORMS_TALLER_1_ARMAMENT_H
