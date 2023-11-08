//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include <iostream>
#include "Worm.h"
#include "../../ConfigureParameters/ConfigParameters.h"

Worm::Worm() : GameObject(ENTITY_WORM) {
}

Worm::Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX), positionInitialY(posIniY) {
    this->idWorm = idWorm;
    hp = 100.0f;
    dragSpeed = 0.2f;
    directionLook = Direction::RIGHT;
    jumpForward = std::make_pair(1.0f, 0.5f);
    jumpBack = std::make_pair(0.2f, 1.2f);
    typeFocus = NO_FOCUS;
    typeMov = STANDING;
}

void Worm::assignBonusLife() {
    hp += LIFE_BONUS;
}

void Worm::addToTheWorld(b2World *world) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.fixedRotation = true;
    wormDef.position.Set(positionInitialX, positionInitialY);
    wormDef.userData.pointer = (uintptr_t) this;
    this->body = world->CreateBody(&wormDef);

    b2CircleShape wormShape;
    wormShape.m_p.Set(0.0f, 1.0f);
    wormShape.m_radius = 0.2f;
    b2FixtureDef defFixtureWorm;
    defFixtureWorm.shape = &wormShape;
    defFixtureWorm.friction = 1.0f;
    defFixtureWorm.density = 1.0f;
    this->body->CreateFixture(&defFixtureWorm);
}

void Worm::jumpBackwards() {
    if( not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * jumpBack.second / jumpBack.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(jumpBack.first * 10.0f / (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita);
        float speedY = initialSpeed * sin(angleTita);

        float impulseX = body->GetMass() * speedX;
        float impulseY = body->GetMass() * speedY;

        if (directionLook == RIGHT) {
            impulseX = -impulseX;
            directionLook = LEFT;       // Gusano "Da una vuelta hacia atras" mira al lado opuesto esta OK.
        } else if (directionLook == LEFT) {
            directionLook = RIGHT;   //MIRAMOS LADO OPUESTO AL Saltar hacia atras.
        } // ^

        b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
}
void Worm::jumpForwards() {
    if(not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)) {
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * jumpForward.second / jumpForward.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(jumpForward.first * 10.0f /
                            (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita);
        float speedY = initialSpeed * sin(angleTita);

        float impulseX = body->GetMass() * speedX;
        float impulseY = body->GetMass() * speedY;
        if (directionLook == LEFT) {
            impulseX = -impulseX;
        }
        b2Vec2 impulse(impulseX, impulseY); //  por la gravedad
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
}
void Worm::walk(Direction aDirection) {
    this->typeMov = MoveWorm::WALKING;
    if(not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) {
        directionLook = aDirection;
        /*
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
        float impulse = body->GetMass() * speed;
        if (directionLook == Direction::LEFT ) {
            impulse = -impulse;
        }
        b2Vec2 impulseSpeed(impulse, 0.0f); //  por la gravedad
        body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
        */
        b2Vec2 velocity = body->GetLinearVelocity();
        velocity.x = SPEED_WORM;//upwards - don't change x velocity
        if (directionLook == Direction::LEFT ) {
            velocity.x = -SPEED_WORM;
        }
        body->SetLinearVelocity(velocity);
    }
}

bool Worm::isInContactWithAnotherWorm(){
    for(b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next){ // iterar sobre todos los contactos de un cuerpo:
        GameObject* aGameObj = (GameObject*) ce->contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        GameObject* aOtherGamObj = (GameObject*) ce->contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        if ( aGameObj->getEntityType() == ENTITY_WORM and aOtherGamObj->getEntityType() == ENTITY_WORM ){
            return true;
        }
    }
    return false;
}

Direction Worm::getDirectionLook() const {
    return this->directionLook;
}

float Worm::getPositionX() const {
    return this->body->GetWorldCenter().x;
}

float Worm::getPositionY() {
    return this->body->GetWorldCenter().y;
}

float Worm::getHP() const {
    return this->hp;
}

TypeFocusWorm Worm::getTypeFocusWorm() const {
    return this->typeFocus;
}

void Worm::activateFocus() {
    this->typeFocus = TypeFocusWorm::FOCUS;
}

MoveWorm Worm::getTypeMov() const {
    return typeMov;
}

void Worm::leftWorm() {
    // chequeo si esta con un arma entonces solo cambiar la dirreccio hacia donde mira.
    walk(Direction::LEFT);
}

void Worm::rightWorm() {
    walk(Direction::RIGHT);
}




