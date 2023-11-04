//
// Created by abraham on 03/11/23.
//

#include <iostream>
#include "MyContactListener.h"
#include "Worm.h"
#include "Beam.h"

// funciones de la colision que usaremos en el map.

void wormCollidesWithBeam(GameObject* worm, GameObject* beam){
    std::cout << "Worm colisionar con el beam\n";
    Worm* unWorm = (Worm*) (worm);
    Beam* unaBeam = (Beam*) (beam);
    //unWorm->startContact();
}

void beamCollideWithWorm(GameObject* beam, GameObject* worm){
    std::cout << "BEAM colisionar con el WORM\n";
    wormCollidesWithBeam(worm, beam);
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


MyContactListener::MyContactListener(b2World *world){
    world->SetContactListener(this);
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_BEAM)] = &wormCollidesWithBeam;
    collisionsMap[std::make_pair(ENTITY_BEAM, ENTITY_WORM)] = &beamCollideWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_WATER)] = &wormCollidesWithWater;
    collisionsMap[std::make_pair(ENTITY_WATER, ENTITY_WORM)] = &waterCollidesWithWorm;
    collisionsMap[std::make_pair(ENTITY_WORM, ENTITY_EDGE)] = &wormCollidesWithEdege;
    collisionsMap[std::make_pair(ENTITY_EDGE, ENTITY_WORM)] = &edgeCollidesWithWorm;
}

void MyContactListener::BeginContact(b2Contact* contact){
    GameObject* gameObject = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    GameObject* otroGameObject = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData().pointer;  // me devuelve un uintptr_t lo casteo a gameObject.
    if(gameObject == nullptr || otroGameObject == nullptr) return;
    auto iteratorElement =  collisionsMap.find( std::make_pair(gameObject->getEntityType(), otroGameObject->getEntityType())); // nos retorna un iterador
    std::cout << "gameObject->getEntityType()" << gameObject->getEntityType() << "\n";
    std::cout << "otroGameObject->getEntityType()" << otroGameObject->getEntityType() << "\n";
    if(iteratorElement != collisionsMap.end() ){
        std::cout << "iteratorElement != collisionsMap.end()\n";
        auto hitFunction = iteratorElement->second;
        if(hitFunction){
            hitFunction(gameObject, otroGameObject);
        }
    }

}