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
        if(aMissile!= nullptr and aMissile->isDestroyedBody()){
            ProjectileDTO aProjectileDTO =  aMissile->getProjectilDTO();
            aProjectileDTO.setTypeExplode(EXPLODE);
            lastProjectilesDTO.push_back(aProjectileDTO);
            aWorld->DestroyBody(aMissile->getBody());
            aMissile = nullptr;
        }
    }
}

void AirAttackDetonator::getProjectilesDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
    for(auto& missilesDestroyed: lastProjectilesDTO){
        vecProjectileDTO.push_back(missilesDestroyed);
    }
    lastProjectilesDTO.clear(); // limpiamos el vector ya enviamos los misiles destruidos .

    //ahora enviamos los q no estan destruidos.
    for(auto& aMissile : missiles){
        if( aMissile != nullptr and not aMissile->isDestroyedBody()){
            vecProjectileDTO.push_back(aMissile->getProjectilDTO());
        }
    }
}



