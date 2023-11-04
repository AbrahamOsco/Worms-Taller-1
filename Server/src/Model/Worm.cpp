//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include "Worm.h"

Worm::Worm(const size_t &idWorm, const float &posIniX, const float &posIniY) : GameObject(ENTITY_WORM), positionInitialX(posIniX), positionInitialY(posIniY) {
    this->idWorm = idWorm;
    hp = 100.0f;
    dragSpeed = 0.2f;
    directionLook = Direction::RIGHT;
    jumpForward = std::pair<float,float>{1.0f, 0.5f};
    jumpBack = std::pair<float,float>{0.2f, 1.2f};
}

void Worm::assignBonusLife() {
    hp += LIFE_BONUS;
}

WormDTO Worm::getWormInitialDTO() const {
    return WormDTO(idWorm, positionInitialX, positionInitialY);
}

void Worm::addToTheWorld(b2World *world) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.fixedRotation = true;
    wormDef.position.Set(positionInitialX, positionInitialY);
    wormDef.userData.pointer = (uintptr_t) this;
    this->body = world->CreateBody(&wormDef);

    //  creamos la forma del gusano.
    b2CircleShape wormShape;
    wormShape.m_p.Set(10.0f, 10.0f);
    wormShape.m_radius = 1.0f;

    b2FixtureDef defFixtureWorm;
    defFixtureWorm.shape = &wormShape;
    defFixtureWorm.friction = 4.0f;
    defFixtureWorm.density = 1.0f;
    this->body->CreateFixture(&defFixtureWorm);
}

void Worm::jumpBackwards() {
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
void Worm::jumpForwards() {
    if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
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
    if(abs(body->GetLinearVelocity().x) < 2.0f && abs(body->GetLinearVelocity().y) < 2.0f) {
        directionLook = aDirection;
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * 10.0f; // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
        float impulse = body->GetMass() * speed;
        if (directionLook == Direction::LEFT ) {
            impulse = -impulse;
        }
        b2Vec2 impulseSpeed(impulse, 0.0f); //  por la gravedad
        body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
    }
}



