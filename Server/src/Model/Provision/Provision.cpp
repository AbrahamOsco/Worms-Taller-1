//
// Created by abraham on 19/11/23.
//

#include <iostream>
#include "Provision.h"
#include "../Worm/Worm.h"

Provision::Provision(const float &positionX, const float &positionY, const TypeEffect &typeEffect,
                     const GameParameters &parameters) : GameObject(ENTITY_PROVISION), typeEffect(typeEffect), gameParameters(parameters) {
    position = std::make_pair(positionX, positionY);
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
    boxDefFixture.friction = 1.0f;
    boxDefFixture.density = 1.0f;
    this->world = world;
    this->body->CreateFixture(&boxDefFixture);
    inContact = false;
}

void Provision::getProvisionDTO(std::vector<ProvisionDTO> &vecProvisionDTO) {
    ProvisionDTO aProvisionDTO = ProvisionDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                                              this->gameParameters.getMaxHeightPixel() - this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(),
                                              typeEffect, NO_CONTACT);
    if(this->isDestroyedBody() and inContact ) {
        inContact = false;
        aProvisionDTO.setTypeContact(CONTACT);
        vecProvisionDTO.push_back(aProvisionDTO);
    }
    else if (not this->isDestroyedBody()){
        vecProvisionDTO.push_back(aProvisionDTO);
    }
}

void Provision::applyEffect(Worm *wormSelect) {
    if(typeEffect == MEDICAL_KIT){
        wormSelect->giveExtraHP(gameParameters.getProvisionExtraHP());
        std::cout << "Worm  with giveExtraHP\n";
    } else if (typeEffect == MUNITIONS){
        wormSelect->giveExtraMunition(gameParameters.getProvisionExtraMunition());
        std::cout << "Worm  with giveExtraMunition\n";
    } else if ( typeEffect == EXPLOSION){
        b2Vec2 impulseExplosion(gameParameters.getProvisionImpulseExplosionX(), gameParameters.getProvisionImpulseExplosionY());
        if(wormSelect->getDirection() == RIGHT){
            impulseExplosion.x *=(-1);
        }
        wormSelect->getBody()->ApplyLinearImpulse( impulseExplosion, wormSelect->getBody()->GetWorldCenter(), true);
        float damageExplosion = gameParameters.getProvisionDamageExplosion();
        wormSelect->takeDamage(damageExplosion);
        std::cout << "Worm  with explosion\n";
    }
    // destroyed the provision
    this->destroyBody();
    inContact = true;
}

