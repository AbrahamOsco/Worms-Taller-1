//
// Created by abraham on 21/11/23.
//

#include "Dynamite.h"

Dynamite::Dynamite(const int &waitTime, const GameParameters &gameParameters, const TypeFocus &typeFocus) : GameObject(ENTITY_DYNAMITE),
          waitTime(waitTime), exploded(false), explodable(50.0f, 4.0f, 2.0f), gameParameters(gameParameters), typeFocus(typeFocus) {
}

void Dynamite::addToTheWorld(b2World* aWorld, b2Vec2 position){
    startTime = std::chrono::steady_clock::now();
    b2BodyDef dynamiteDef;
    dynamiteDef.type = b2_dynamicBody;
    dynamiteDef.fixedRotation = true;
    dynamiteDef.position.Set(position.x, position.y );
    dynamiteDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&dynamiteDef);
    b2CircleShape dynamiteForm;
    dynamiteForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
    dynamiteForm.m_radius = 0.1f;

    b2FixtureDef defFixDynamite;
    defFixDynamite.shape = &dynamiteForm;
    defFixDynamite.friction = 20.0f;
    defFixDynamite.density = 1.0f; // ver el tema del aire luego.
    this->body->CreateFixture(&defFixDynamite);
    this->world = aWorld;
}

void Dynamite::passTime(){
    time = std::chrono::steady_clock::now();
    if (time - startTime >= waitTime && !exploded)
        explode();
}

void Dynamite::explode(){
    exploded = true;
    body->ApplyLinearImpulse(b2Vec2(0.0f,0.03f),body->GetWorldCenter(),true); // para que se despegue y vuelva a chocar con la viga.

}

bool Dynamite::hasExploded() const{
    return exploded;
}

void Dynamite::searchWormAndCollide(const b2Vec2 &projectilePosition) {
    explodable.searchWormAndCollide(projectilePosition, world);
    this->destroyBody();
}

ProjectileDTO Dynamite::getProjectilDTO() {
    return ProjectileDTO(DYNAMITE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() -this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(), this->typeFocus, NO_EXPLODE);
}

