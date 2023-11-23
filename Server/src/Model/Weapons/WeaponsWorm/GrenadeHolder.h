//
// Created by abraham on 22/11/23.
//

#ifndef WORMS_TALLER_1_GRENADEHOLDER_H
#define WORMS_TALLER_1_GRENADEHOLDER_H


#include "Weapon.h"
#include "../WeaponSight/WeaponSight.h"
#include "../../Projectiles/Grenades/Grenade/Grenade.h"

class GrenadeHolder : public Weapon {
private:
    std::pair<float, float> impulseWeapon; // impulse x, impulse y
    WeaponSight weaponSight;
    std::unique_ptr<Grenade> grenade;
    std::pair<float, float> maxImpulseWeapon;
    int explosionIterations;

public:
    explicit GrenadeHolder(const TypeWeapon& aTypeWeapon, const float &damagePrincipal, const TypeMunition& aTypeMunition,
                     const size_t& aMunition, const GameParameters& gameParameters);

    void passTime() override;

    void increaseAngle() override;

    void decreaseAngle() override;

    bool hasAScope() override;

    bool hasVariablePower() override;

    bool increaseImpulse() override;

    bool launchesProjectiles() override;

    bool thereAreProjectiles() override;

    void getProjectilesDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    void tryCleanProjectiles(b2World* aWorld) override;

    bool hasMunition() const override;

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) override;


    void attack(const TypeWeapon &typeGrenade, const b2Vec2 &positionWorm, const Direction &direction,
                const TypeFocus &typeFocus, const int &timeWait, b2World *world);


    void getProjectilesDTOPrimary(std::vector<ProjectileDTO> &vecProjectileDTO);
};


#endif //WORMS_TALLER_1_GRENADEHOLDER_H
