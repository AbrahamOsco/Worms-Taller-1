//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include "MortarMainProjectile.h"
#include "../MortarFragment/MortarFragment.h"

MortarMainProjectile::MortarMainProjectile(const GameParameters &gameParameters, const TypeFocus &typeFocus)
        : ProjectileMortar(gameParameters, typeFocus) {
    fragmentImpulses = {b2Vec2(-gameParameters.fragmentGetMidDist(), gameParameters.fragmentGetMidDist()),
                        b2Vec2(-gameParameters.fragmentGetLongDist(), gameParameters.fragmentGetShortDist()),
                        b2Vec2(gameParameters.fragmentGetLongDist(), gameParameters.fragmentGetShortDist()),
                        b2Vec2(gameParameters.fragmentGetMidDist(), gameParameters.fragmentGetMidDist()),
                        b2Vec2(gameParameters.fragmentGetShortDist(), gameParameters.fragmentGetLongDist()),
                        b2Vec2(-gameParameters.fragmentGetShortDist(), gameParameters.fragmentGetLongDist())};

    this->explodable = Explodable(gameParameters.mortarGetMainDamage(),
        gameParameters.mortarGetMaxRadio(), gameParameters.mortarGetMaxImpulse());
    wasThrowFragments = false;
}

void MortarMainProjectile::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    if ( this->isDestroyedBody() && !wasThrowFragments ) {
        wasThrowFragments = true;
        this->throwFragments();
    }

    vecProjectileDTO.push_back(ProjectileDTO(PROJ_MORTAR,
    this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
    gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                             this->typeFocus, NO_EXPLODE) );
}

void MortarMainProjectile::throwFragments() {
    for (auto & impulse : fragmentImpulses) {
        std::unique_ptr<ProjectileMortar> projectileMortar{new MortarFragment(gameParameters, typeFocus)};
        projectileMortar->addToTheWorld(body->GetWorld(), body->GetWorldCenter() + impulse, impulse, windValue);
        fragments.push_back(std::move(projectileMortar));
    }
}

bool MortarMainProjectile::hasFragment() const {
    for (auto& aFragment : fragments) {
        if (aFragment != nullptr) {
            return true;
        }
    }
    return false;
}

void MortarMainProjectile::tryCleanProjectiles() {
    for ( auto& aFragmentMortar : fragments ) {
        if (aFragmentMortar!= nullptr && aFragmentMortar->isDestroyedBody() &&
                !aFragmentMortar->hasExplosionIterations()) {
            this->body->GetWorld()->DestroyBody(aFragmentMortar->getBody());
            aFragmentMortar = nullptr;
        } else if ( aFragmentMortar != nullptr && !aFragmentMortar->isDestroyedBody() ) {
            // para q no se quede en el aire
            float smallImpulse = 0.01f;  // Ajusta según sea necesario
            this->body->ApplyLinearImpulse(b2Vec2(0.0f, -1*smallImpulse), body->GetWorldCenter(), true);
        }
    }
}

void MortarMainProjectile::getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for ( auto& aFragment : fragments ) {
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

void MortarMainProjectile::searchWormAndCollide(const b2Vec2 &projectilePosition) {
    ProjectileMortar::searchWormAndCollide(projectilePosition);
}

void MortarMainProjectile::awakenFragments() {
    size_t fragmentsNull = 0;
    for (auto& aFragment : fragments) {
        if (aFragment == NULL) {
            fragmentsNull++;
        }
    }
    for (auto& aFragment : fragments) {
        if (aFragment != nullptr && fragmentsNull == 5) {
            float impulseToEndTurn = -1.0f;
            aFragment->getBody()->ApplyLinearImpulse(b2Vec2(0.5, impulseToEndTurn),
                aFragment->getBody()->GetWorldCenter(), true);
        }
    }
}
