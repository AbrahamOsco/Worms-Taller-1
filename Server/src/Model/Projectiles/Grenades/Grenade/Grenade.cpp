//
// Created by abraham on 22/11/23.
//

#include <iostream>
#include <vector>
#include "Grenade.h"

Grenade::Grenade(GameParameters gameParameters, const int &waitTime, const TypeFocus& typeFocus) :
        GameObject(ENTITY_GRENADE), gameParameters(gameParameters), waitTime(waitTime),
         typeFocus(typeFocus), explodable(0.0f, 0.0f, 0.0f), fixedRotation(true), world(nullptr) {
    exploded = false;
    collided = false;
    explosionIterations = gameParameters.getAnimationIterations();
    restitution = 0.0;
}

void Grenade::addToTheWorld(b2World* aWorld, b2Vec2 positionOrigen, b2Vec2 impulseGrenade) {
    explosionIterations = gameParameters.getAnimationIterations();
    b2BodyDef grenadeDef;
    grenadeDef.type = b2_dynamicBody;
    grenadeDef.bullet = true;
    grenadeDef.fixedRotation = this->fixedRotation;
    grenadeDef.position.Set(positionOrigen.x, positionOrigen.y);
    grenadeDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&grenadeDef);
    b2CircleShape grenadeForm;
    grenadeForm.m_p.Set(0.0f, 0.0f);
    grenadeForm.m_radius = 0.1f;

    b2FixtureDef defFixGrenade;
    defFixGrenade.shape = &grenadeForm;
    defFixGrenade.density = 1.0f;
    defFixGrenade.restitution = this->restitution;
    this->body->CreateFixture(&defFixGrenade);
    body->ApplyLinearImpulse(impulseGrenade, body->GetWorldCenter(), true);
    this->world = aWorld;
}

void Grenade::collide() {
    if (!collided) {
        collided = true;
        startTime = std::chrono::steady_clock::now();
    }
}

void Grenade::passTime() {
    if (collided) {
        time = std::chrono::steady_clock::now();
        if (time - startTime >= waitTime && !exploded) {
            explode();
        }
    }
}

void Grenade::explode() {
    this->exploded = true;
    explodable.searchWormAndCollide(body->GetWorldCenter(), world);
    this->destroyBody();
}


void Grenade::throwFragments() {
}


bool Grenade::hasExplosionIterations() const {
    return explosionIterations > 0;
}

void Grenade::removeAIteration() {
    explosionIterations--;
}

int Grenade::getNumberIterations() const {
    return explosionIterations;
}

bool Grenade::hasFragment() const {
    return false;
}

void Grenade::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
}



