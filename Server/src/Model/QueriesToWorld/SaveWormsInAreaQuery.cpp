//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "SaveWormsInAreaQuery.h"

SaveWormsInAreaQuery::SaveWormsInAreaQuery(const b2Vec2 &munitionPosition){

}

bool SaveWormsInAreaQuery::ReportFixture(b2Fixture* fixture){
    std::cout << "En SaveWormsInAreaQuery entre a reportFixture tengo que reportar que encontre un objeto en el intervalo del cuadrado\n";
    GameObject* obj = (GameObject*) (fixture->GetBody()->GetUserData().pointer);
    if (obj && obj->getEntityType() == ENTITY_WORM) {
        std::cout << "Ese objeto es un worm entro al report fiture de query\n";
        float distanceSquared = b2DistanceSquared(munitionPosition, fixture->GetBody()->GetWorldCenter()); // sacamos la distancia al cuadrado
        // es decir distancia = c.c -> c = (a-b) = (x1-x2; y1-y2) -> c.c = (x1-x2)² + (y1-y2)²
        std::cout << "obj" << obj << "\n";
        wormAndDistanceSquar[obj] = distanceSquared;
    }
    return true; // Continuar con la búsqueda
}

std::map<GameObject *, float> SaveWormsInAreaQuery::getWormsAndDistSquared() const {
    return this->wormAndDistanceSquar;
}
