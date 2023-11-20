//
// Created by abraham on 19/11/23.
//

#include "Provision.h"
#include "../Worm/Worm.h"

Provision::Provision(const float &positionX, const float &positionY, const TypeEffect &typeEffect,
                     const GameParameters &parameters) : GameObject(ENTITY_PROVISION), typeEffect(typeEffect), gameParameters(parameters) {
    position = std::make_pair(positionX, positionY);
}

void Provision::addToTheWorld(b2World *world) {
    b2BodyDef boxProvDef;
    boxProvDef.type = b2_staticBody;
    boxProvDef.fixedRotation = true;
    boxProvDef.position.Set(position.first, position.second);
    boxProvDef.userData.pointer = (uintptr_t) this;
    this->body = world->CreateBody(&boxProvDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.25, 0.25f);
    b2FixtureDef boxDefFixture;
    boxDefFixture.shape = &boxShape;
    boxDefFixture.friction = 1.0f;
    boxDefFixture.density = 1.0f;
    this->world = world;
    this->body->CreateFixture(&boxDefFixture);
}

ProvisionDTO Provision::getProvisionDTO() const {
    return ProvisionDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                        this->gameParameters.getMaxHeightPixel() - this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(),
                        typeEffect);
}

void Provision::applyEffect(Worm *wormSelect) {
    if(typeEffect == MEDICAL_KIT){
        wormSelect->giveExtraHP(25.0f);
    } else if (typeEffect == MUNITIONS){
        wormSelect->giveExtraMunition(10);
    } else if ( typeEffect == EXPLOSION){
        b2Vec2 directionExplosion = this->getBody()->GetWorldCenter() - wormSelect->getBody()->GetWorldCenter();
        directionExplosion.Normalize();
        float impulseExplosion = 0.5f;
        wormSelect->getBody()->ApplyLinearImpulse(impulseExplosion * directionExplosion, wormSelect->getBody()->GetWorldCenter(), true);
        float damageExplosion = 15.0f;
        wormSelect->takeDamage(damageExplosion);
        this->destroyBody();
    }
}

