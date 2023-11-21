//
// Created by abraham on 20/11/23.
//

#ifndef WORMS_TALLER_1_AIRATTACKDETONATOR_H
#define WORMS_TALLER_1_AIRATTACKDETONATOR_H


#include "Weapon.h"
#include "../../Projectiles/AirAttackMissile.h"

class AirAttackDetonator : public Weapon {
private:
    std::vector<std::unique_ptr<AirAttackMissile>> missiles;
    std::vector<float> offsets;
    b2World* world;
    TypeFocus typeFocus;

public:
    AirAttackDetonator(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
                       const size_t &aMunition, const GameParameters &gameParameters);

    void detonate(const int &posXAttack, const int &posYAttack, b2World *world, const TypeFocus &typeFocus);

    // metodos necesarios a overridear
    bool hasAScope() override;

    bool hasVariablePower() override;

    bool launchesProjectiles() override;

    bool thereAreProjectiles() override;

    void tryCleanProjectiles(b2World* aWorld) override;

    void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;


};


#endif //WORMS_TALLER_1_AIRATTACKDETONATOR_H