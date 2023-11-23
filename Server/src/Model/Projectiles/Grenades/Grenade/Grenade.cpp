//
// Created by abraham on 22/11/23.
//

#include "Grenade.h"

Grenade::Grenade(GameParameters gameParameters, const int &waitTime) : GameObject(ENTITY_GRENADE), gameParameters(gameParameters), weaponSight(3.0f, 2.0f, gameParameters) {
    exploded = false;
    collided = false;
}

void Grenade::addToTheWorld(b2World* aWorld, b2Vec2 positionOrigen, b2Vec2 impulseGrenade){
    b2BodyDef grenadeDef;
    grenadeDef.type = b2_dynamicBody;
    grenadeDef.fixedRotation = this->fixedRotation;
    grenadeDef.position.Set(positionOrigen.x, positionOrigen.y );
    grenadeDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&grenadeDef);
    b2CircleShape grenadeForm;
    grenadeForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
    grenadeForm.m_radius = 0.1f;

    b2FixtureDef defFixGrenade;
    defFixGrenade.shape = &grenadeForm;
    defFixGrenade.density = 1.0f; // ver el tema del aire luego.
    defFixGrenade.restitution = this->restitution;
    this->body->CreateFixture(&defFixGrenade);
    body->ApplyLinearImpulse( impulseGrenade, body->GetWorldCenter(), true);
    this->world = aWorld;
}

void Grenade::collide(){
    if (!collided) {
        collided = true;
        startTime = std::chrono::steady_clock::now();
    }
}

bool Grenade::hasExploded() const {
    return exploded;
}

void Grenade::throwFragments(std::vector<std::unique_ptr<Grenade>>* grenades){


}

ProjectileDTO Grenade::getProjectilDTO() {
    return ProjectileDTO();
}



