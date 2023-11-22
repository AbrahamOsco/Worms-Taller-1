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

    void detonate(const int &posXAttack, b2World *world, const TypeFocus &typeFocus);

    // Estos 3 override obligatoriamente
    bool hasAScope() override;

    bool hasVariablePower() override;

    bool launchesProjectiles() override;

    // esto 3 para las armas que lanzan proyectiles overridear obligatorioriamente.

    bool thereAreProjectiles() override;

    void tryCleanProjectiles(b2World* aWorld) override;

    void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    // para las armas que gastan municiones;
    bool hasMunition() const override;


};


#endif //WORMS_TALLER_1_AIRATTACKDETONATOR_H
