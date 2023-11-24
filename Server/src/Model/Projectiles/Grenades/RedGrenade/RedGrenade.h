//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_REDGRENADE_H
#define WORMS_TALLER_1_REDGRENADE_H


#include "../Grenade/Grenade.h"

class RedGrenade : public Grenade {
private:
    std::vector<b2Vec2> fragmentImpulses;
    std::vector<std::unique_ptr<Grenade>> fragmentGrenades;
public:
    RedGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;

    void throwFragments() override;

    void explode() override;

    ~RedGrenade() = default;

    void passTime() override;

    bool hasFragment() const override;

    void tryCleanProjectiles();

    void getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO);
};


#endif //WORMS_TALLER_1_REDGRENADE_H
