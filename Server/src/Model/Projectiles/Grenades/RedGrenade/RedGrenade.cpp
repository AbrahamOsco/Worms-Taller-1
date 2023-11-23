//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "RedGrenade.h"
#include "../FragmentGrenade/FragmentGrenade.h"

RedGrenade::RedGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus)
        : Grenade(gameParameters, waitTime, typeFocus){
    fragmentImpulses = {b2Vec2(-0.1f,0.1f), b2Vec2(-0.137f,0.027f), b2Vec2(0.137f,0.027f), b2Vec2(0.1f,0.1f), b2Vec2(0.027f,0.137f), b2Vec2(-0.027f,0.137f)};
    fixedRotation = true;
    restitution = 0.0f;
    this->explodable = Explodable(30.0f, 2.0f, 1.0f);
}

void RedGrenade::throwFragments(){
    for (auto & impulse : fragmentImpulses) {
        std::unique_ptr<Grenade> grenade{new FragmentGrenade(gameParameters, 0, typeFocus)};
        grenade->addToTheWorld(body->GetWorld(), body->GetWorldCenter() + impulse, impulse);
        std::cout << "Lanzando grenade fragment en x: " << (body->GetWorldCenter().x + impulse.x)  << "  y  :" << (body->GetWorldCenter().y + impulse.y) << "\n";
        fragmentGrenades.push_back(std::move(grenade));
    }
}

void RedGrenade::explode() {
    Grenade::explode();
    this->throwFragments();
}

void RedGrenade::tryCleanProjectiles(){
    for(auto& aFragmentGrenade :fragmentGrenades ){
        if(aFragmentGrenade!= nullptr and aFragmentGrenade->isDestroyedBody() and not aFragmentGrenade->hasExplosionIterations()){
            this->body->GetWorld()->DestroyBody(aFragmentGrenade->getBody());
            aFragmentGrenade = nullptr;
        }
    }
}

bool RedGrenade::hasFragment() const {
    for(auto& aFragment : fragmentGrenades){
        if(aFragment != nullptr){
            return true;
        }
    }
    return false;
}

void RedGrenade::getFragmentProjectilDTO(std::vector<ProjectileDTO> &vecProjectileDTO){
    for(auto& aFragment :fragmentGrenades ){
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


void RedGrenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    ProjectileDTO aProjectilDTO = ProjectileDTO(PROJ_RED_GRENADE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                                gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                                                this->typeFocus, NO_EXPLODE);
    vecProjectileDTO.push_back(aProjectilDTO);
}

void RedGrenade::passTime() {
    Grenade::passTime();
    if(not hasFragment()){
        return;
    }
    // hacemos pasar el tiempo a los fragmentos
    for(auto& aFragment :fragmentGrenades ){
        if(aFragment != nullptr){
            aFragment->passTime();
        }
    }
}

