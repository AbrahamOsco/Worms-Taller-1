//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "GameContactListener.h"
#include "../Worm/Worm.h"
#include "../QueriesToWorld/SaveWormsInAreaQuery.h"
#include "../Scenario/Beam/Beam.h"

// Clase de colisiones el listener:
void wormCollidesWithBeam(GameObject* worm, GameObject* beam){
    std::cout << "Worm colisionar con el WORM\n";
    Worm* unWorm = (Worm*) (worm);
    Beam* unaBeam = (Beam*) (beam);
    if(unaBeam->getAngle() >0 and unaBeam->getAngle() <= 45){
        unWorm->activaeInclinedBeam();
    } else if ( unaBeam->getAngle() == 0 ){
        unWorm->disableInclinedBeam();
    }
    // calcualamos danio.
    float positionYInAirLast = unWorm->getPositionAir().second;
    float positionYCurrent = unWorm->getBody()->GetWorldCenter().y;
    float fallHeight = positionYInAirLast - positionYCurrent;
    float thresholdFall = 2.0f; // sacar del archivo @ricardo.
    std::cout << "Altura e la caida actual fue de  " << fallHeight << "\n";
    if (fallHeight > thresholdFall){
        std::cout << "Superamos el treshhold la caida es de " << fallHeight;
        fallHeight -= thresholdFall;
        int damageForFall = (int) std::min(fallHeight, 25.0f);
        unWorm->takeDamage(damageForFall);
        if(unWorm->getHP() <= 0){
            unWorm->destroyBody();
        }
    }
    //actualizamos la posicion en el aire gusano luego de caer.
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void beamCollideWithWorm(GameObject* beam, GameObject* worm){
    wormCollidesWithBeam(worm, beam);
    std::cout << "BEAM colisionar con el WORM\n";
}

void wormCollidesWithWater(GameObject* worm, GameObject* water){
    std::cout << "Worm colisionar con WATER\n";
    worm->destroyBody();
}
void waterCollidesWithWorm(GameObject* water, GameObject* worm){
    std::cout << "Water colisionar con el Worm\n";
    wormCollidesWithWater(worm, water);
}
void wormCollidesWithEdege(GameObject* worm, GameObject* edge){
    std::cout << "Worm collisiona con el edge\n";
}
void edgeCollidesWithWorm(GameObject* edge, GameObject* worm){
    std::cout << "Edge collisiona con el worm\n";
}

void wormCollidesWithWorm(GameObject* worm1, GameObject* worm2){
    Worm* aWorm1 = (Worm*) (worm1);
    Worm* aWorm2 = (Worm*) (worm2);
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

void munitionBazookaCollidesWithWorm(GameObject* bazooka, GameObject* worm){
    std::cout << "munitionBazookaCollidesWithWorm\n";
    if(bazooka == nullptr or worm == nullptr) return;
    Worm* wormSelect = (Worm*) (worm);
    bazooka->destroyBody();
    wormSelect->takeDamage(50.0f);
    if (wormSelect->getHP() <= 0.0f){
        wormSelect->destroyBody();
    }
}

void wormCollidesWithMunitionBazooka(GameObject* worm1, GameObject* bazooka){
    std::cout << "wormCollidesWithMunitionBazooka\n";
    munitionBazookaCollidesWithWorm(bazooka, worm1);
}

void munitionBazookaCollideWithBeam(GameObject* munitionBazooka, GameObject* beam){
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

void beamCollidesWithMunitionBazooka(GameObject* beam, GameObject* munitionBazooka){
    std::cout << "beamCollidesWithMunitionBazooka\n";
    munitionBazookaCollideWithBeam(munitionBazooka, beam);
}

void beamEndContactWithWorm(GameObject* beam, GameObject* worm){
    std::cout << "beamEndContactWithWorm\n";
    Worm* unWorm = (Worm*) (worm);
    Beam* unaBeam = (Beam*) (beam);
    b2Vec2 positonWormInAir = worm->getBody()->GetWorldCenter();
    unWorm->savePositionInAir(positonWormInAir.x, positonWormInAir.y);
}

void wormEndContactWithBeam(GameObject* worm, GameObject* beam){
    std::cout << "wormEndContactWithBeam\n ";
    beamEndContactWithWorm(beam, worm);
}


GameContactListener::GameContactListener(b2World *aWorld) {
    aWorld->SetContactListener(this);
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM)] = &wormCollidesWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM)] = &beamCollideWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WATER)] = &wormCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_WORM)] = &waterCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE)] = &wormCollidesWithEdege;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM)] = &edgeCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WORM)] = &wormCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BAZOOKA_PROJECTILE)] = &wormCollidesWithMunitionBazooka;
    collisionsMap[std::make_pair(ENTITY_BAZOOKA_PROJECTILE, ENTITY_BEAM)] = &munitionBazookaCollideWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_BAZOOKA_PROJECTILE )] = &beamCollidesWithMunitionBazooka;
    endContactMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM) ] = &beamEndContactWithWorm;
    endContactMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM) ] = &wormEndContactWithBeam;
}


void GameContactListener::BeginContact(b2Contact *contact) {
    std::cout << "inica colision en beginCOntact\n";
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    std::cout << "Collision detected between " << gameObject->getEntityType() << " and " << otroGameObject->getEntityType() << "\n";
    if(iteratorElement != collisionsMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject);
        }
    }
}

void GameContactListener::EndContact(b2Contact *contact) {
    std::cout << "termina el contacto \n";
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  endContactMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    std::cout << "Collision finished between " << gameObject->getEntityType() << " and " << otroGameObject->getEntityType() << "\n";
    if(iteratorElement != endContactMap.end() ){
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject);
        }
    }
}


