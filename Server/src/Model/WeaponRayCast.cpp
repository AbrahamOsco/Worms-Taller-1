//
// Created by abraham on 10/11/23.
//

#include <iostream>
#include "WeaponRayCast.h"
#include "GameObject.h"

WeaponRayCast::WeaponRayCast() : body(nullptr), point(b2Vec2(0.0f, 0.0f)), normal(b2Vec2(0.0f, 0.0f)), fraction(0.0f){}

float WeaponRayCast::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) {
    std::cout << "Entre a reportFixture Esto signfica que colisone con algo y hay que reportarlo \n";
    std::cout << "Colisiono a  un" << fraction*100 << " % de la trayectura total \n";
    GameObject* gameObject = (GameObject*) fixture->GetBody()->GetUserData().pointer;
    this->body = fixture->GetBody();
    this->point = point;
    this->normal = normal;
    this->fraction = fraction;
    return fraction;
}

b2Body *WeaponRayCast::getBody() const{
    return this->body;
}

float WeaponRayCast::getFraction() const {
    return this->fraction;
}

void WeaponRayCast::resetRayCast() {
    this->body = nullptr;
    this->fraction = 0.0f;
    this->point = this->normal = b2Vec2(0.0, 0.0f);
}


