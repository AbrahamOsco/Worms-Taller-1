//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "GameContactListener.h"
#include "../Worm/Worm.h"
#include "../QueriesToWorld/SaveWormsInAreaQuery.h"
#include "../Scenario/Beam/Beam.h"

// Clase de colisiones el listener:
void wormCollidesWithBeam(GameObject* worm, GameObject* beam, GameParameters *gameParameters){
    std::cout << "Worm colisionar con el BEAM\n";
    Worm* unWorm = (Worm*) (worm);
    unWorm->assigOnABeam();
    Beam* unaBeam = (Beam*) (beam);
    if(unaBeam->getAngle() > 0.0f and unaBeam->getAngle() <= GameParameters::getBeamMinimumScalableAngle()){
        unWorm->activaeInclinedBeam();
    } else if ( unaBeam->getAngle() == 0 ){
        unWorm->disableInclinedBeam();
    }
    // calcualamos danio.
    float positionYInAirLast = unWorm->getPositionAir().second;
    float positionYCurrent = unWorm->getBody()->GetWorldCenter().y;
    float fallHeight = positionYInAirLast - positionYCurrent;
    float thresholdFall = gameParameters->getWormMaxResistanceToHeight();
    if (fallHeight > thresholdFall){
        fallHeight -= thresholdFall;
        int damageForFall = (int) std::min(fallHeight, gameParameters->getMaxFallDamage());
        unWorm->takeDamage(damageForFall);
    }
    //actualizamos la posicion en el aire gusano luego de caer.
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void beamCollidesWithWorm(GameObject* beam, GameObject* worm, GameParameters *gameParameters ){
    wormCollidesWithBeam(worm, beam, gameParameters);
}

void wormCollidesWithWater(GameObject* worm, GameObject* water, GameParameters *gameParameters){
    std::cout << "Worm colisionar con WATER\n";
    worm->destroyBody();
}
void waterCollidesWithWorm(GameObject* water, GameObject* worm, GameParameters *gameParameters){
    wormCollidesWithWater(worm, water, gameParameters);
}
void wormCollidesWithEdege(GameObject* worm, GameObject* edge, GameParameters *gameParameters){
    std::cout << "Worm collisiona con el edge\n";
}
void edgeCollidesWithWorm(GameObject* edge, GameObject* worm, GameParameters *gameParameters){
    std::cout << "Edge collisiona con el worm\n";
}

void wormCollidesWithWorm(GameObject* worm1, GameObject* worm2, GameParameters *gameParameters){
    Worm* aWorm1 = (Worm*) (worm1);
    Worm* aWorm2 = (Worm*) (worm2);
    aWorm1->assigNextToAWorm();
    aWorm2->assigNextToAWorm();
    if (aWorm1->getBody()->GetLinearVelocity().x > 0 ){
        std::cerr << "Worm 1 choco con velocidad a Worm 2 asi que le reducimos a cero para q no lo empuje\n";
        b2Vec2 velocity = aWorm1->getBody()->GetLinearVelocity();
        velocity.x = 0.0f;
        aWorm1->getBody()->SetLinearVelocity(velocity);
    } else if ( aWorm2->getBody()->GetLinearVelocity().x > 0 ){
        std::cerr << "Worm 2 choco con velocidad a Worm 1 asi que le reducimos a cero para q no lo empuje\n";
        b2Vec2 velocity = aWorm1->getBody()->GetLinearVelocity();
        velocity.x = 0.0f;
        aWorm2->getBody()->SetLinearVelocity(velocity);
    }
}

void projectileBazookaCollidesWithWorm(GameObject* projectileBazooka, GameObject* worm, GameParameters *gameParameters){
    std::cout << "munitionBazookaCollidesWithWorm\n";
    if(projectileBazooka == nullptr or worm == nullptr) return;
    Worm* wormSelect = (Worm*) (worm);
    projectileBazooka->destroyBody();
    wormSelect->takeDamage(50.0f);  // todo queda pendiente ver esto y hacerlo en area.
    // aca aplicar el daño en area.
}

void wormCollidesWithProjectileBazooka(GameObject* worm1, GameObject* projectileBazooka, GameParameters *gameParameters){
    projectileBazookaCollidesWithWorm(projectileBazooka, worm1, gameParameters);
}

void projectileBazookaCollideWithBeam(GameObject* munitionBazooka, GameObject* beam, GameParameters *gameParameters){
    std::cout << "munitionBazookaCollideWithBeam\n";
    b2Vec2 munitionPosition = munitionBazooka->getBody()->GetWorldCenter();

    ProjectileBazooka* munitionSelect = (ProjectileBazooka*)  munitionBazooka;
    SaveWormsInAreaQuery savWormsinArea(munitionPosition);     // Función de devolución de llamada para la búsqueda

    Beam * beamSelected = (Beam*) beam;
    beamSelected->getWorld()->QueryAABB(&savWormsinArea, munitionSelect->getAreaForSearch(munitionPosition));
    for(auto& aElement : savWormsinArea.getWormsAndDistSquared() ){
        Worm* aWormToTakeDamage = (Worm*)(aElement.first);
        b2Vec2 impulseForWorm = munitionSelect->getImpulseForWorm(aWormToTakeDamage->getBody()->GetWorldCenter(), munitionPosition, aElement.second);
        float damageForWorm = munitionSelect->getDamageForWorm(aElement.second);
        aWormToTakeDamage->getBody()->ApplyLinearImpulse( impulseForWorm, aWormToTakeDamage->getBody()->GetWorldCenter(), true);
        aWormToTakeDamage->takeDamage(damageForWorm);
    }
    munitionBazooka->destroyBody();
}

void beamCollidesWithMunitionBazooka(GameObject* beam, GameObject* munitionBazooka, GameParameters *gameParameters){
    projectileBazookaCollideWithBeam(munitionBazooka, beam, gameParameters);
}

void beamEndContactWithWorm(GameObject* beam, GameObject* worm, GameParameters *gameParameters){
    std::cout << "beamEndContactWithWorm\n";
    Worm* unWorm = (Worm*) (worm);
    unWorm->unAssingOnABeam();
    Beam* unaBeam = (Beam*) (beam);
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void wormEndContactWithBeam(GameObject* worm, GameObject* beam, GameParameters *gameParameters){
    beamEndContactWithWorm(beam, worm, gameParameters);
}

void wormEndContactWithWorm(GameObject* worm, GameObject* wormTwo, GameParameters *gameParameters){
    Worm* aWorm1 = (Worm*) (worm);
    Worm* aWorm2 = (Worm*) (wormTwo);
    aWorm1->unAssignNextToAWorm();
    aWorm2->unAssignNextToAWorm();
}


GameContactListener::GameContactListener(b2World *world, GameParameters *gameParameters) {
    world->SetContactListener(this);
    this->gameParameters = (GameParameters *) gameParameters;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM)] = &wormCollidesWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM)] = &beamCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WATER)] = &wormCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_WORM)] = &waterCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE)] = &wormCollidesWithEdege;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM)] = &edgeCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WORM)] = &wormCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BAZOOKA_PROJECTILE)] = &wormCollidesWithProjectileBazooka;
    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_BEAM)] = &projectileBazookaCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_BAZOOKA_PROJECTILE )] = &beamCollidesWithMunitionBazooka;


    endContactMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM) ] = &beamEndContactWithWorm;
    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM) ] = &wormEndContactWithBeam;
    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_WORM) ] = &wormEndContactWithWorm;

}


void GameContactListener::BeginContact(b2Contact *contact) {
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    if(iteratorElement != collisionsMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject, gameParameters);
        }
    }
}

void GameContactListener::EndContact(b2Contact *contact) {
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  endContactMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    if(iteratorElement != endContactMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject, gameParameters);
        }
    }
}


