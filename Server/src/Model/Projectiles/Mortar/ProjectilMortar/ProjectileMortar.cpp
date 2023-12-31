//
// Created by abraham on 23/11/23.
//

#include "ProjectileMortar.h"

ProjectileMortar::ProjectileMortar(const GameParameters &gameParameters, const TypeFocus &typeFocus)
        : GameObject(ENTITY_MORTAR_PROJECTILE), gameParameters(gameParameters),
        typeFocus(typeFocus), explodable(0.0f, 0.0f, 0.0f), aWorld(nullptr)  {
    explosionIterations = gameParameters.getAnimationIterations();
    this->windValue = 0.0f;
}

void ProjectileMortar::addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile,
                                     const float &windValue) {
    this->windValue = windValue;
    explosionIterations = gameParameters.getAnimationIterations();
    b2BodyDef projMortarDef;
    projMortarDef.type = b2_dynamicBody;
    projMortarDef.fixedRotation = true;
    projMortarDef.bullet = true;
    projMortarDef.position.Set(positionP2.x, positionP2.y);
    projMortarDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&projMortarDef);
    b2CircleShape projMortarShape;
    projMortarShape.m_p.Set(0.0f, 0.0f);
    projMortarShape.m_radius = 0.1f;

    b2FixtureDef defFixProjMortar;
    defFixProjMortar.friction = 0.2f;
    defFixProjMortar.shape = &projMortarShape;
    defFixProjMortar.density = 1.0f;
    this->body->CreateFixture(&defFixProjMortar);

    float windValueSelect = windValue/ this->body->GetMass();
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true);

    body->ApplyLinearImpulse(impulseProjectile, body->GetWorldCenter(), true);
    this->aWorld = aWorld;
}

void ProjectileMortar::searchWormAndCollide(const b2Vec2 &projectilePosition) {
    explodable.searchWormAndCollide(projectilePosition, aWorld);
    this->destroyBody();
}

void ProjectileMortar::throwFragments() {
}

void ProjectileMortar::getProjectileDTO(std::vector<ProjectileDTO> &vecProjectileDTO) {
}

void ProjectileMortar::removeAIteration() {
    explosionIterations--;
}

bool ProjectileMortar::hasExplosionIterations() const {
    return (explosionIterations > 0);
}

int ProjectileMortar::getNumberIterations() const {
    return explosionIterations;
}



