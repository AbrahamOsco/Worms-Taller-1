//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "RedGrenade.h"
#include "../FragmentGrenade/FragmentGrenade.h"

RedGrenade::RedGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus)
        : Grenade(gameParameters, waitTime, typeFocus) {
    fragmentImpulses = {b2Vec2(-gameParameters.fragmentGetMidDist(), gameParameters.fragmentGetMidDist()),
                        b2Vec2(-gameParameters.fragmentGetLongDist(), gameParameters.fragmentGetShortDist()),
                        b2Vec2(gameParameters.fragmentGetLongDist(), gameParameters.fragmentGetShortDist()),
                        b2Vec2(gameParameters.fragmentGetMidDist(), gameParameters.fragmentGetMidDist()),
                        b2Vec2(gameParameters.fragmentGetShortDist(), gameParameters.fragmentGetLongDist()),
                        b2Vec2(-gameParameters.fragmentGetShortDist(), gameParameters.fragmentGetLongDist())};

    fixedRotation = true;
    this->explodable = Explodable(gameParameters.redGrenadeGetMainDamage(),
    gameParameters.redGrenadeGetMaxRadio(), gameParameters.redGrenadeGetMaxImpulse());
}



void RedGrenade::throwFragments() {
    for (auto & impulse : fragmentImpulses) {
        std::unique_ptr<Grenade> grenade{new FragmentGrenade(gameParameters, 0, typeFocus)};
        grenade->addToTheWorld(body->GetWorld(), body->GetWorldCenter() + impulse, impulse);
        fragmentGrenades.push_back(std::move(grenade));
    }
}

void RedGrenade::explode() {
    Grenade::explode();
    this->throwFragments();
}

void RedGrenade::tryCleanProjectiles() {
    for ( auto& aFragmentGrenade : fragmentGrenades ) {
        if (aFragmentGrenade!= nullptr && aFragmentGrenade->isDestroyedBody() &&
                !aFragmentGrenade->hasExplosionIterations()) {
            this->body->GetWorld()->DestroyBody(aFragmentGrenade->getBody());
            aFragmentGrenade = nullptr;
        }
    }
}

bool RedGrenade::hasFragment() const {
    for (auto& aFragment : fragmentGrenades) {
        if (aFragment != nullptr) {
            return true;
        }
    }
    return false;
}

void RedGrenade::getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for ( auto& aFragment : fragmentGrenades ) {
        if ( aFragment != nullptr && aFragment->isDestroyedBody() && aFragment->hasExplosionIterations() ) {
            aFragment->getProjectileDTO(vecProjectileDTO);
            ProjectileDTO* projectileDto = &vecProjectileDTO.back();
            projectileDto->setTypeExplode(EXPLODE);
            if (aFragment->getNumberIterations() == gameParameters.getAnimationIterations()) {
                projectileDto->setTypeExplode(EXPLODE_SOUND);
            }
            aFragment->removeAIteration();
        } else if (aFragment != nullptr && !aFragment->isDestroyedBody()) {
            aFragment->getProjectileDTO(vecProjectileDTO);
        }
    }
}


void RedGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_RED_GRENADE,
    this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
    gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                                this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}

void RedGrenade::passTime() {
    Grenade::passTime();
    if (!hasFragment()) {
        return;
    }
    // hacemos pasar el tiempo a los fragmentos
    for ( auto& aFragment : fragmentGrenades ) {
        if (aFragment != nullptr) {
            aFragment->passTime();
        }
    }
}

