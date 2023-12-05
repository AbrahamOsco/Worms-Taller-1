//
// Created by abraham on 09/11/23.
//

#ifndef WORMS_TALLER_1_ARMAMENT_H
#define WORMS_TALLER_1_ARMAMENT_H


#include <map>
#include <memory>
#include <box2d/b2_world.h>
#include "../../../../../Common/DTO/WormDTO.h"
#include "../../../../../Common/DTO/WeaponsDTO.h"
#include "../../../../GameParameters/GameParameters.h"
#include "../WeaponsWorm/Weapon.h"
#include "../../../../../Common/DTO/ProjectilesDTO.h"

class Armament {
 private:
    size_t idPlayer;
    std::map<TypeWeapon, std::unique_ptr<Weapon> > armament;  // si no funcionan usaremos unique_ptr en weapon
    TypeWeapon currentWeapon;
    TypeWeapon weaponOnStandBy;
    const GameParameters& gameParameters;

 public:
    Armament(const size_t &idPlayer, const GameParameters &gameParameters);

    Weapon *getWeaponCurrentPtr();

    TypeWeapon getWeaponCurrent() const;

    bool isUnarmed() const;

    void putWeaponOnStandByAndUnarmed();

    void getWeaponOnStandBy(const bool &attacked);

    void assignWeapon(const TypeWeapon &weapon, const Direction &direction);

    WeaponsDTO getWeaponsDTO() const;

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent);

    ProjectilesDTO getProjectilesDTO(const bool &attackedWorm);

    void tryCleanProjectiles(b2World *aWorld);

    void endTurn();

    bool thereAreProjectiles();

    bool weaponStandByLaunchesProjectiles();

    void assignWindValue(const float &aWindValue);

    void giveExtraMunition(const size_t &extraMunition);

    void updateTime(const bool &attacked);

    bool hasMunition();

    bool isAGrenade() const;

    void
    attackWithGrenade(const b2Vec2 &positionWorm, const Direction &direction, const TypeFocus &focus,
                      const int &waitTime,
                      b2World *aWorld);
};


#endif  // WORMS_TALLER_1_ARMAMENT_H
