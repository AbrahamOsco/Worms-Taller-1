//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Bat.h"
#include "GameObject.h"

Bat::Bat(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
         const size_t &aMunition) : Weapon(aTypeWeapon, damagePrincipal, aTypeMunition, aMunition){
    impulseX = 0.30f;
    impulseY = 0.42;
    rayAngle = 0.0f; // esta todo el rato en grados
    rayLength = 3.0f;
}

// Devuelve null si no impacto con un worm si impacto con un gusano devuelve el gusano.(GameObject)
GameObject* Bat::getBodyShocked(b2World *world, const b2Vec2& positionWorm) {
    b2Vec2 p1 = positionWorm;
    float factor = 1.0f;
    if(direction == LEFT){
        factor = -1.0f;
    }
    b2Vec2 p2 = p1 + rayLength * b2Vec2(factor * cosf(rayAngle * DEGRATORADIANS) , sinf(rayAngle * DEGRATORADIANS)); // aca pasamos rayAngle a grados.
    world->RayCast(&weaponRayCast, p1, p2);
    std::cout << "myFirstRayCast->getFraction(): " << weaponRayCast.getFraction() << "\n";
    if ( weaponRayCast.getFraction() <= 0.001f ){
        std::cout << "Practicamente no colisione con nada ni recorri el 1% de la trayectoria asi que salgo\n";
        return nullptr;
    }
    GameObject* gameObject = (GameObject*) weaponRayCast.getBody()->GetUserData().pointer;
    if ( gameObject != nullptr and gameObject->getEntityType() == ENTITY_WORM){
        std::cout << "colisione con un gusano ahora le bajo la vida a punta de un golpe \n";
        return gameObject;
    }
    return nullptr;
}

float Bat::getImpulseX() const {
    return impulseX;
}

float Bat::getImpulseY() const {
    return impulseY;
}

void Bat::riseAngle() {
    rayAngle += 10.0f;
    if(rayAngle > 90.0f){
        rayAngle -= 10.0f;
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";

    /*
    rayAngle += (10.0f * DEGRATORADIANS ); // angulo lo pasamos a radianes
    if (rayAngle >= ((b2_pi/2) + 0.01f) ){
        rayAngle -= (10.0f * DEGRATORADIANS ); // volvemos al estado anterior
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle * RADIANSTODEGREE << " / " <<  rayAngle << " \n";
    */

}
void Bat::lowerAngle() {
    rayAngle -= 10.0f;
    if (rayAngle < -90.0f){
        rayAngle += 10.0f;
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";

    /*
    rayAngle -= (10.0f * DEGRATORADIANS);
    if (rayAngle <= ((-b2_pi/2) - 0.01f) ){
        rayAngle += (10.0f * DEGRATORADIANS); // volvemos al estado anterior.
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle * RADIANSTODEGREE << " / " <<  rayAngle << " \n";
    */

}


bool Bat::hasAScope(){
    return true;
}

void Bat::changeDirection(const Direction &aDirection) {
    this->direction = aDirection;
    std::cerr << "Cambio mando la direccion actual del bate a" << aDirection << "\n";
}


void Bat::prepareWeapon(const Direction &aDirection) {
    this->direction = aDirection;
}

void Bat::resetRayCast(){
    this->weaponRayCast.resetRayCast();
}

