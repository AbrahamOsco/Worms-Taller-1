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
    iterationsForBatAttack = 15;
    positionInAir= std::make_pair(0.0f, 0.0f);
}

void Worm::savePositionInAir(const float &positionXAir, const float &positionYAir) {
    positionInAir = std::make_pair(positionXAir, positionYAir);
}

std::pair<float, float>  Worm::getPositionAir() const{
    return positionInAir;
}

void Worm::activaeInclinedBeam() {
    this->onInclinedBeam = true;
}

void Worm::disableInclinedBeam() {
    this->onInclinedBeam = false;
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

// for worm moves.

void Worm::jump(const TypeJump& typeJump){
    if( not isInContactWithAnotherWorm() and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
        armament.putWeaponOnStandByAndUnarmed(); // guardamos el arma actual y nos desarmamos
        float distanceX = distancesJumpForward.first;
        float distanceY = distancesJumpForward.second;
        if(typeJump == JUMP_BACKWARDS){
            distanceX = distancesJumpBack.first;
            distanceY = distancesJumpBack.second;
        }
        this->typeMov = JUMPING;
        float angleTita = atan(4.0f * distanceY / distanceX);       //  (4 *hmax)/distMaxHorizontal.
        float initialSpeed = sqrt(distanceX * (gameParameters.getGravity() * -1) / (sin(2 * angleTita))); // el 1.0f hace referencia distancia horizontal de 1.0m;
        float speedX = initialSpeed * cos(angleTita), speedY = initialSpeed * sin(angleTita);
        float impulseX = body->GetMass() * speedX, impulseY = body->GetMass() * speedY;

        if( typeJump == JUMP_BACKWARDS){
            if (directionLook == RIGHT) {
                impulseX = -impulseX;
                directionLook = LEFT;
            } else if (directionLook == LEFT) {
                directionLook = RIGHT;
            }
        } else if ( typeJump == JUMP_FORWARDS){
            if (directionLook == LEFT) {
                impulseX = -impulseX;
            }
        }
        b2Vec2 impulse(impulseX, impulseY); //  por la gravedaddfd
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

void Worm::leftWorm() {
    if( armament.isUnarmed() ){
        walk(Direction::LEFT);
    } else if ( not armament.isUnarmed() and this->directionLook == Direction::LEFT ){
        armament.putWeaponOnStandByAndUnarmed();
        walk(Direction::LEFT);
    } else{             // no esta desarmando y estaba mirando a la derecha pasamos a que mire a la izquierda
        this->directionLook = Direction::LEFT;
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
    }
}

void Worm::upWorm() {
    if(this->armament.getWeaponCurrent()  == NONE_WEAPON){
        return;
    }
    this->armament.getWeaponCurrentPtr()->increaseAngle();
}

void Worm::downWorm() {
    if(this->armament.getWeaponCurrent()  == NONE_WEAPON){
        return;
    }
    this->armament.getWeaponCurrentPtr()->decreaseAngle();
}

// geters.
MoveWorm Worm::getTypeMov() const {
    return typeMov;
}

TypeFocusWorm Worm::getTypeFocusWorm() const {
    return this->typeFocus;
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
TypeWeapon Worm::getWeaponCurrent() const {
    return this->armament.getWeaponCurrent();
}

float Worm::getHP() const {
    return this->hp;
}

// DTOS.
WormDTO Worm::getWormDTO() const {
    return WormDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                   gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                   this->idPlayer, this->hp, this->directionLook, this->typeFocus, this->typeMov, this->armament.getWeaponCurrent() );

}
WeaponSightDTO Worm::getWeaponSightDTO() {
    return armament.getWeaponSightDTO(this->body->GetWorldCenter(), directionLook);
}

ProjectilesDTO Worm::getProjectilesDTO() {
    return armament.getProjectilesDTO();
}

void Worm::activateFocus() {
    this->typeFocus = TypeFocusWorm::FOCUS;
}

void Worm::updateState() {
    if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
        if(this->typeMov == ATTACKING and iterationsForBatAttack > 0 ){
            std::cout << "Iteracion para mostrar el ataque con el bate" << typeMov << "\n";
            iterationsForBatAttack--;
        } else if ( this->typeMov== ATTACKING and iterationsForBatAttack == 0){
            iterationsForBatAttack = 15;
            this->typeMov = STANDING;
        } else{
            this->typeMov = STANDING;
        }
        armament.getWeaponOnStandBy();
    }
}

// weapons.
void Worm::takeDamage(const float &aDamage){
    this->hp -=aDamage;
    if(hp <=0.0){
        this->destroyBody();
    }
}

void Worm::assignWeapon(const TypeWeapon& aTypeWeapon){
    armament.assignWeapon(aTypeWeapon, this->directionLook);
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
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    }
    if( this->armament.getWeaponCurrent() == BASEBALL_BAT){
        this->typeMov = ATTACKING;
        this->attackWithBat();
    } else if ( this->armament.getWeaponCurrent() == BAZOOKA){
        this->attackWithBazooka();
    }
    attacked = true;
}

void Worm::attackWithBazooka() {
    Bazooka *bazooka = (Bazooka *) armament.getWeaponCurrentPtr();
    bazooka->shootProjectile(aWorld, this->getBody()->GetWorldCenter(), directionLook);
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

void Worm::teleportWorm(const float& posXTeleport, const float& posYTeleport){
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport);
}

