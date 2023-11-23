//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "MortarMainProjectile.h"
#include "../MortarFragment/MortarFragment.h"

MortarMainProjectile::MortarMainProjectile(const GameParameters &gameParameters, const TypeFocus &typeFocus)
        : ProjectileMortar(gameParameters, typeFocus) {
    this->explodable = Explodable(50.0f, 2, 1.0f);
}

void MortarMainProjectile::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    vecProjectileDTO.push_back(ProjectileDTO(PROJ_MORTAR, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                             gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                             this->typeFocus, NO_EXPLODE) );
}

void MortarMainProjectile::throwFragments() {
    for (auto & impulse : fragmentImpulses) {
        std::unique_ptr<ProjectileMortar> projectileMortar{new MortarFragment(gameParameters, typeFocus)};
        projectileMortar->addToTheWorld(body->GetWorld(), body->GetWorldCenter() + impulse, impulse, windValue );
        std::cout << "Lanzando mortar fragment en x: " << (body->GetWorldCenter().x + impulse.x)  << "  y  :" << (body->GetWorldCenter().y + impulse.y) << "\n";
        fragments.push_back(std::move(projectileMortar));
    }
}

bool MortarMainProjectile::hasFragment() const {
    for(auto& aFragment : fragments){
        if(aFragment != nullptr){
            return true;
        }
    }
    return false;
}

void MortarMainProjectile::tryCleanProjectiles() {
    for(auto& aFragmentMortar :fragments ){
        if(aFragmentMortar!= nullptr and aFragmentMortar->isDestroyedBody() and not aFragmentMortar->hasExplosionIterations()){
            this->body->GetWorld()->DestroyBody(aFragmentMortar->getBody());
            aFragmentMortar = nullptr;
        }
    }
}

void MortarMainProjectile::getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for(auto& aFragment :fragments ){
        if(aFragment != nullptr and aFragment->isDestroyedBody() and aFragment->hasExplosionIterations() ){
            aFragment->getProjectileDTO(vecProjectileDTO);
            ProjectileDTO* projectileDto = &vecProjectileDTO.back(); // saco unar referencia del ultimo q pushee para setearle el typeEXplode
            projectileDto->setTypeExplode(EXPLODE);
            if(aFragment->getNumberIterations() == 15.0f){
                projectileDto->setTypeExplode(EXPLODE_SOUND);
            }
            aFragment->removeAIteration();
        } else if (aFragment != nullptr and not aFragment->isDestroyedBody()){
            aFragment->getProjectileDTO(vecProjectileDTO);
        }
    }

}
