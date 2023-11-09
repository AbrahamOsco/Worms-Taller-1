//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include <iostream>
#include "Worm.h"
#include "../../GameParameters//GameParameters.h"

Worm::Worm(const size_t &idWorm, const float &posIniX, const float &posIniY, const GameParameters& gameParameter) : GameObject(ENTITY_WORM),
                positionInitialX(posIniX), positionInitialY(posIniY), gameParameter(gameParameter) {
    this->idWorm = idWorm;
    hp = gameParameter.getInitialHPWorm();
    dragSpeed = gameParameter.getWormDragSpeed();
    directionLook = Direction::RIGHT;
    distancesJumpForward = std::make_pair(gameParameter.getDistXForwardJump(), gameParameter.getDistYForwardJump());
    distancesJumpBack = std::make_pair(gameParameter.getDistXBackJump(), gameParameter.getDistYBackJump());
    typeFocus = NO_FOCUS;
    typeMov = STANDING;
}

void Worm::assignBonusLife() {
    hp += gameParameter.getWormHPBonus();
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
    wormShape.m_radius = gameParameter.getHalfHeightWorm();
    b2FixtureDef defFixtureWorm;
    defFixtureWorm.shape = &wormShape;
    defFixtureWorm.friction = gameParameter.getFrictionWorm();
    defFixtureWorm.density = 1.0f;
    this->body->CreateFixture(&defFixtureWorm);
}

void Worm::jumpBackwards() {
    if( not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
        this->typeMov = JUMPING;
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * distancesJumpBack.second / distancesJumpBack.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(distancesJumpBack.first * (gameParameter.getGravity()*-1) / (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita);
        float speedY = initialSpeed * sin(angleTita);

        float impulseX = body->GetMass() * speedX;
        float impulseY = body->GetMass() * speedY;

        if (directionLook == RIGHT) {
            impulseX = -impulseX;
            directionLook = LEFT;
        } else if (directionLook == LEFT) {
            directionLook = RIGHT;
        }
        b2Vec2 impulse(impulseX, impulseY); //  por la gravedaddfd
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
}
void Worm::jumpForwards() {
    if(not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)) {
        this->typeMov = JUMPING;
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * distancesJumpForward.second / distancesJumpForward.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(distancesJumpForward.first * (gameParameter.getGravity()*-1) /
                            (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita);
        float speedY = initialSpeed * sin(angleTita);

        float impulseX = body->GetMass() * speedX;
        float impulseY = body->GetMass() * speedY;
        if (directionLook == LEFT) {
            impulseX = -impulseX;
        }
        b2Vec2 impulse(impulseX, impulseY);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
}
void Worm::walk(Direction aDirection) {
    if(not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) {
        this->typeMov = MoveWorm::WALKING;
        directionLook = aDirection;
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * (gameParameter.getGravity()*-1); // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
        float impulse = body->GetMass() * speed;
        if (directionLook == Direction::LEFT ) {
            impulse = -impulse;
        }
        b2Vec2 impulseSpeed(impulse, 0.0f); //  por la gravedad
        body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
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

void Worm::stopIfUnmoving() {
    if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
        this->typeMov = STANDING;
    }
}




