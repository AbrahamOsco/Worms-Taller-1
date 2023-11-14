//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_ARMAMENT_H
#define WORMS_TALLER_1_ARMAMENT_H


#include <map>
#include <memory>
#include "../../../../../Common/DTO/WormDTO.h"
#include "../../../../../Common/DTO/WeaponsDTO.h"
#include "../../../../GameParameters/GameParameters.h"
#include "../WeaponsWorm/Weapon.h"

class Armament {
private:
    size_t idPlayer;
    std::map<TypeWeapon, std::unique_ptr<Weapon> > armament; // si no funcionan usaremos unique_ptr en weapon
    TypeWeapon currentWeapon;
    TypeWeapon weaponOnStandBy;
    const GameParameters& gameParameters;
public:
    Armament(const size_t &idPlayer, const GameParameters &gameParameters);

    bool hasAWeapon();

    Weapon *getWeaponCurrentPtr();

    TypeWeapon getWeaponCurrent() const;

    bool isUnarmed() const;

    bool hasAScoped();

    //void changeDirection(const Direction &direction);

    void putWeaponOnStandByAndUnarmed();

    void getWeaponOnStandBy();

    void assignWeapon(const TypeWeapon &weapon, const Direction &direction);

    WeaponsDTO getWeaponsDTO() const;

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent);
};


#endif //WORMS_TALLER_1_ARMAMENT_H