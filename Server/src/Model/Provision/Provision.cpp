//
// Created by abraham on 19/11/23.
//

#include <iostream>
#include "Provision.h"
#include "../Worm/Worm.h"

Provision::Provision(const float &positionX, const float &positionY, const TypeEffect &typeEffect,
                    const GameParameters &parameters) : GameObject(ENTITY_PROVISION), typeEffect(typeEffect),
                    gameParameters(parameters), world(nullptr) {
    position = std::make_pair(positionX, positionY);
    animationIterations = gameParameters.getAnimationIterations();
}

void Provision::addToTheWorld(b2World *world) {
    b2BodyDef boxProvDef;
    boxProvDef.type = b2_dynamicBody;
    boxProvDef.fixedRotation = true;
    boxProvDef.position.Set(position.first, position.second);
    boxProvDef.userData.pointer = (uintptr_t) this;
    this->body = world->CreateBody(&boxProvDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(gameParameters.getProvisionHalfHeight(), gameParameters.getProvisionHalfHeight());
    b2FixtureDef boxDefFixture;
    boxDefFixture.shape = &boxShape;
    boxDefFixture.friction = 0.1f;
    boxDefFixture.density = 1.0f;
    this->world = world;
    this->body->CreateFixture(&boxDefFixture);
    animationIterations = gameParameters.getAnimationIterations();
}

void Provision::getProvisionDTO(std::vector<ProvisionDTO> &vecProvisionDTO) {
    ProvisionDTO aProvisionDTO = ProvisionDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
        this->gameParameters.getMaxHeightPixel() - this->body->GetWorldCenter().y
        *gameParameters.getPositionAdjustment(),
                                              typeEffect, NO_CONTACT);
    if (this->isDestroyedBody() && animationIterations > 0) {
        aProvisionDTO.setTypeContact(CONTACT);
        if ( animationIterations == gameParameters.getAnimationIterations() ) {
            aProvisionDTO.setTypeContact(CONTACT_SOUND);
        }
        vecProvisionDTO.push_back(aProvisionDTO);
        animationIterations--;
    } else if (!this->isDestroyedBody()) {
        vecProvisionDTO.push_back(aProvisionDTO);
    }
}

void Provision::applyEffect(Worm *wormSelect) {
    if (typeEffect == MEDICAL_KIT) {
        wormSelect->giveExtraHP(gameParameters.getProvisionExtraHP());
    } else if (typeEffect == MUNITIONS) {
        wormSelect->giveExtraMunition(gameParameters.getProvisionExtraMunition());
    } else if (typeEffect == EXPLOSION) {
        b2Vec2 impulseExplosion(gameParameters.getProvisionImpulseExplosionX(),
            gameParameters.getProvisionImpulseExplosionY());
        if (wormSelect->getDirection() == RIGHT) {
            impulseExplosion.x *=(-1);
        }
        wormSelect->getBody()->ApplyLinearImpulse(impulseExplosion, wormSelect->getBody()->GetWorldCenter(), true);
        float damageExplosion = gameParameters.getProvisionDamageExplosion();
        wormSelect->takeDamage(damageExplosion);
    }
    this->destroyBody();
    animationIterations = gameParameters.getAnimationIterations();
}

bool Provision::hasIterations() const {
    return (this->animationIterations > 0);
}
