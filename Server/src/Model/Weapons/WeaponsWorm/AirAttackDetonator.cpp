//
// Created by abraham on 20/11/23.
//

#include "AirAttackDetonator.h"
// @ todo eliminar numeros magicos
AirAttackDetonator::AirAttackDetonator(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
                  const size_t &aMunition, const GameParameters &gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition,gameParameters) {
    offsets = {-0.5f,0.5f,-1.5f,1.5f,-2.5f,2.5f};
}

void AirAttackDetonator::detonate(const int &posXAttack, b2World *world, const TypeFocus &typeFocus) {
    float posXInMeters =  (float) posXAttack / gameParameters.getPositionAdjustment();
    for (auto & offset : offsets) {
        std::unique_ptr<AirAttackMissile> missile{new AirAttackMissile(gameParameters, typeFocus)};
        missile.get()->addToTheWorld(world, b2Vec2(posXInMeters + offset, gameParameters.airAttackGetPositionY()), windValue );
        missiles.push_back(std::move(missile));
    }
    this->munition--;
}

bool AirAttackDetonator::hasAScope() {
    return false;
}

bool AirAttackDetonator::hasVariablePower() {
    return false;
}

bool AirAttackDetonator::launchesProjectiles() {
    return true;
}

bool AirAttackDetonator::thereAreProjectiles() {
    for(auto& aMissile: missiles){
        if(aMissile != nullptr ){
            return true;
        }
    }
    return false;
}

void AirAttackDetonator::tryCleanProjectiles(b2World *aWorld) {
    for(auto& aMissile: missiles){
        if(aMissile!= nullptr and aMissile->isDestroyedBody() and not aMissile->hasExplosionIterations() ){
            aWorld->DestroyBody(aMissile->getBody());
            aMissile = nullptr;
        }
    }
}

void AirAttackDetonator::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for(auto& aMissile : missiles){
        if(aMissile != nullptr and aMissile->isDestroyedBody() and aMissile->hasExplosionIterations()){
            ProjectileDTO aProjectilDto = aMissile->getProjectilDTO();
            aProjectilDto.setTypeExplode(EXPLODE);
            if(aMissile->getNumberIterations() == 15){
                aProjectilDto.setTypeExplode(EXPLODE_SOUND);
            }
            vecProjectileDTO.push_back(aProjectilDto);
            aMissile->removeAIteration();
        }
        else if( aMissile != nullptr and not aMissile->isDestroyedBody() ){
            vecProjectileDTO.push_back(aMissile->getProjectilDTO());
        }
    }
}

bool AirAttackDetonator::hasMunition() const {
    return (this->munition >0);
}



