//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include <iostream>
#include "Worm.h"
#include "../../../GameParameters/GameParameters.h"

Worm::Worm(const size_t &idWorm, const size_t &idPlayer,  const float &posIniX, const float &posIniY, const GameParameters &gameParameter,
           Armament& armament) : GameObject(ENTITY_WORM), idWorm(idWorm), idPlayer(idPlayer),
                                 positionInitialX(posIniX), positionInitialY(posIniY), gameParameters(gameParameter), aWorld(nullptr), armament(armament) {
    hp = gameParameter.getInitialHPWorm();
    dragSpeed = gameParameter.getWormDragSpeed();
    directionLook = Direction::RIGHT;
    distancesJumpForward = std::make_pair(gameParameter.getDistXForwardJump(), gameParameter.getDistYForwardJump());
    distancesJumpBack = std::make_pair(gameParameter.getDistXBackJump(), gameParameter.getDistYBackJump());
    typeFocus = NO_FOCUS;
    typeMov = STANDING;
    onInclinedBeam = false;
    attacked = false;
}

void Worm::assignBonusLife() {
    hp += gameParameters.getWormHPBonus();
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
    wormShape.m_radius = gameParameters.getHalfHeightWorm();
    b2FixtureDef defFixtureWorm;
    defFixtureWorm.shape = &wormShape;
    defFixtureWorm.friction = gameParameters.getFrictionWorm();
    defFixtureWorm.density = 1.0f;
    this->aWorld = world;
    this->body->CreateFixture(&defFixtureWorm);
}

void Worm::jumpBackwards() {
    if( not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
        armament.putWeaponOnStandByAndUnarmed(); // guardamos el arma actual y nos desarmamos
        this->typeMov = JUMPING;
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * distancesJumpBack.second / distancesJumpBack.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(distancesJumpBack.first * (gameParameters.getGravity() * -1) / (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
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
        armament.putWeaponOnStandByAndUnarmed(); // guardamos el arma actual y nos desarmamos
        this->typeMov = JUMPING;
        float angleTita, initialSpeed;
        angleTita = atan(4.0f * distancesJumpForward.second / distancesJumpForward.first);       //  (4 *hmax)/distMaxHorizontal.
        initialSpeed = sqrt(distancesJumpForward.first * (gameParameters.getGravity() * -1) /
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
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * (gameParameters.getGravity() * -1); // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float speed = sqrt(2.0f * acceleration * dragSpeed); // la velocidad la sacamos como 2 * aceleracion * distancia.
        float impulseX = body->GetMass() * speed ;
        float impulseY = 0;
        if (directionLook == Direction::LEFT ) {
            impulseX *=-1;
        }
        if (onInclinedBeam){
            impulseX *= gameParameters.getWormImpulseFactoScalingDown(); // WORM_FACTOR_IMPULSE_SCALING_DOWN
            if (directionLook == Direction::RIGHT){
                impulseX *= gameParameters.getWormImpulseFactorClimbingUp(); // WORM_FACTOR_IMPULSE_CLIMBING_UP
                impulseY = impulseX;
            }
        }
        //std::cout << "Impulse x: " << impulseX << " Impulse y:  " << impulseY << "\n";
        b2Vec2 impulseSpeed(impulseX, impulseY); //  por la gravedad
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

// [todo] Aca Falta hacer gameParameters.getMaxHeightPixel() - (aWormElem.second->getPositionY() * gameParameters.getPositionAdjustment())  para la posicion en Y.

WormDTO Worm::getWormDTO() const {
    return WormDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                   gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                   this->idPlayer, this->hp, this->directionLook, this->typeFocus, this->typeMov, this->armament.getWeaponCurrent() );

}


void Worm::activateFocus() {
    this->typeFocus = TypeFocusWorm::FOCUS;
}


MoveWorm Worm::getTypeMov() const {
    return typeMov;
}

TypeFocusWorm Worm::getTypeFocusWorm() const {
    return this->typeFocus;
}

void Worm::leftWorm() {
    // chequeo si esta con un arma entonces solo cambiar la dirreccio hacia donde mira.
    if( armament.isUnarmed() ){
        walk(Direction::LEFT);
    } else if ( not armament.isUnarmed() and this->directionLook == Direction::LEFT ){
        armament.putWeaponOnStandByAndUnarmed();
        walk(Direction::LEFT);
    } else{             // no esta desarmando y estaba mirando a la derecha pasamos a que mire a la izquierda
        this->directionLook = Direction::LEFT;
        //armament.changeDirection(Direction::LEFT);
    }

}

void Worm::rightWorm() {
    if( armament.isUnarmed()){
        walk(Direction::RIGHT);
    } else if ( not armament.isUnarmed() and this->directionLook == Direction::RIGHT){
        armament.putWeaponOnStandByAndUnarmed();
        walk(Direction::RIGHT);
    } else{         // NO ESTA desarmado y estaba mirando a la izquierda lo hacemos que mira a la derecha
        this->directionLook = Direction::RIGHT;
        //armament.changeDirection(Direction::RIGHT);
    }
}

void Worm::stopIfUnmoving() {
    if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
        if(this->typeMov == ATTACKING){
            std::cout << "Se deja de mostrar el attakking" << typeMov << "\n";
        }
        this->typeMov = STANDING;
        armament.getWeaponOnStandBy();
        /*
        if(armament.getWeaponCurrent() != NONE_WEAPON){
            armament.changeDirection(this->directionLook);
        }
        */
    }
}

void Worm::takeDamage(const float &aDamage){
    this->hp -=aDamage;
    if(hp <=0.0){
        this->destroyBody();
    }
}

// se debe llamar a esta funcion antes de todo para asignar el arma a usar.
void Worm::assignWeapon(const TypeWeapon& aTypeWeapon){
    armament.assignWeapon(aTypeWeapon, this->directionLook);
}

void Worm::attackWithBat(){
    Bat* aBat = (Bat*) this->armament.getWeaponCurrentPtr();
    GameObject* gameObject = aBat->getBodyCollidesWithRayCast(aWorld, this->getBody()->GetWorldCenter(), directionLook);
    if ( gameObject == nullptr){
        std::cout << "No se golpeo a ningun worm \n";         // signfica que no alcanza a nadie nuestro ataque o golpeamos a algo que no es un worm  por ej una viga
        return;
    }
    Worm* worm = (Worm*) gameObject;
    worm->takeDamage(aBat->getMainDamage());  //danio del bate
    float factor = 1.0f;
    if(directionLook == LEFT){
        factor = -1.0f;
    }
    worm->getBody()->ApplyLinearImpulse(b2Vec2(factor * aBat->getImpulseX(), aBat->getImpulseY()), worm->getBody()->GetWorldCenter(), true);
    aBat->resetRayCast();
}

TypeWeapon Worm::getWeaponCurrent() const {
    return this->armament.getWeaponCurrent();
}

void Worm::teleportWorm(const float& posXTeleport, const float& posYTeleport){
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport);
}

WeaponSightDTO Worm::getWeaponSightDTO() {
    return armament.getWeaponSightDTO(this->body->GetWorldCenter(), directionLook);
}

void Worm::activaeInclinedBeam() {
    this->onInclinedBeam = true;
}

void Worm::disableInclinedBeam() {
    this->onInclinedBeam = false;
}

void Worm::upWorm() {
    if(this->armament.getWeaponCurrent()  == NONE_WEAPON){
        return;
    }
    // con esto obtenemos la arma actual por ej un bate y vamos al increaseAngle del bate.
    this->armament.getWeaponCurrentPtr()->increaseAngle();
}

void Worm::downWorm() {
    if(this->armament.getWeaponCurrent()  == NONE_WEAPON){
        return;
    }
    this->armament.getWeaponCurrentPtr()->decreaseAngle();
}

void Worm::increaseImpulse() {
    if(this->armament.getWeaponCurrent()  == NONE_WEAPON){
        return;
    }
    this->armament.getWeaponCurrentPtr()->increaseImpulse();
    if(this->armament.getWeaponCurrentPtr()->hasMaxImpulse() ){
        attack();
    }
}

void Worm::attack() {
    if(this->armament.getWeaponCurrent() == NONE_WEAPON){
        return;
    }
    if(attacked){
        return;
    }

    if( this->armament.getWeaponCurrent() == BASEBALL_BAT){
        this->typeMov = ATTACKING;
        std::cout << "typeMov in attack" << typeMov << "\n";
        this->attackWithBat();
    }

    attacked = true;
}



