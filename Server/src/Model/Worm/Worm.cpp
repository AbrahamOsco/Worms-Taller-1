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
    typeCharge = NONE_CHARGE;
    iterationsForBatAttack = 15;
    positionInAir= std::make_pair(0.0f, 0.0f);
    hpInitialTurn = hp;
    contatctsWithBeam = 0;
    contactsWithWorms = 0;
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
    // polimorfismo aca obtenemos el arma q tengamos actualmente e incrmentamos el angle si algunoas armas haran algo otras no.
    // this->armament.getWeaponCurrentPtr() es remeplazada por el arma actual por ej bat y llama al increasAngle de bat.
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
    //si ataque con el bate sigo teniendo el currentWeaponEnBate hasta q termine el turno en 3 seg.  @todo
    if(typeMov == ATTACKING_WITH_BAT){
        std::vector<ProjectileDTO> vecProjectileDTO;
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    return armament.getProjectilesDTO(attacked);
}

void Worm::activateFocus() {
    this->typeFocus = TypeFocusWorm::FOCUS;
}

void Worm::update() {
    if(this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)){
        if(this->typeMov == ATTACKING_WITH_BAT and iterationsForBatAttack > 0 ){  // el ATTACKING_WITH_BAT ES SOLO PARA BATE asi q no hay problemas.
            iterationsForBatAttack--;
        } else if (this->typeMov == ATTACKING_WITH_BAT and iterationsForBatAttack == 0){
            iterationsForBatAttack = 15;
            this->typeMov = STANDING;
            armament.putWeaponOnStandByAndUnarmed(); // ya paso el frame del ataque con bate asi q lo desarmamos.
        } else{
            this->typeMov = STANDING;
        }
        // @todo creo q luego de disparar volvemos a tener todo armaCurrent en none.
        armament.getWeaponOnStandBy(attacked);
    }
    // si ataca vemos si los proyectiles chocaron al suelo los eliminamos del mundo.
    if(attacked){
        armament.tryCleanProjectiles(aWorld);
    }


}
// weapons.
void Worm::attack() {
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    }
    if( this->armament.getWeaponCurrent() == BASEBALL_BAT){
        this->typeMov = ATTACKING_WITH_BAT;
        this->attackWithBat();
        attacked = true;
    } else if ( this->armament.getWeaponCurrentPtr()->hasVariablePower()){ // en un futuro pregunta si tiene un arma con potencia variable.
        bool reachMaxImpulse = false;
        if(typeCharge == NONE_CHARGE){ // cargo por primera vez.
            typeCharge = MANY_CHARGE;
            reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
        } else if ( typeCharge == MANY_CHARGE) {
            reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
        }
        if(reachMaxImpulse){
            std::cout << "Llege al maximo impulso \n";
            tryAttackVariablePower();
        }
    }
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
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    }
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    float posXInMeters = posXTeleport/60.0F;
    float posYInMeters = (gameParameters.getMaxHeightPixel() - posYTeleport)/60.f;
    teleport->teleportIn(getBody(), posXInMeters, posYInMeters);
    armament.putWeaponOnStandByAndUnarmed(); // luego de atacar con la bazoka pasamos el arma a standB y nos desarmamos
    std::cout << "Me teletransporto en " << posXInMeters << "  " << posYInMeters << "\n";
    attacked = true;
}

void Worm::takeDamage(const float &aDamage){
    std::cout << "Se hace dañño al gusano de " <<  aDamage << "\n";
    this->hp -=aDamage;
    if(hp <=0.0){
        this->destroyBody();
    }
}

void Worm::assignWeapon(const TypeWeapon& aTypeWeapon){
    if( not attacked){
        armament.assignWeapon(aTypeWeapon, this->directionLook);
    }
}

void Worm::endTurn() {
    typeFocus = NO_FOCUS;
    typeMov = STANDING;
    attacked = false;
    armament.endTurn();
    hpInitialTurn = hp;
}
bool Worm::wasDamaged() const{
    return hpInitialTurn != hp;
}

bool Worm::alreadyAttack() const{
    return attacked;
}

void Worm::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft) {
    if(timeLeft <= 0){
        return;
    }
    if(aCommandDTO->getTypeCommand() == TypeCommand::LEFT_CMD ){
        this->leftWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::RIGHT_CMD ){
        this->rightWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_BACK_CMD){
        this->jump(JUMP_BACKWARDS);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_FORWARD_CMD){
        this->jump(JUMP_FORWARDS);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BAT){
        this->assignWeapon(BASEBALL_BAT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_TELEPORT){
        this->assignWeapon(TELEPORT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BAZOOKA){
        this->assignWeapon(BAZOOKA);
    }else if (aCommandDTO->getTypeCommand() == TypeCommand::UP_CMD){
        this->upWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::DOWN_CMD){
        this->downWorm();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::FIRE_CMD){
        this->attack();
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::TELEPORT_MOVE){
        this->teleportWorm(aCommandDTO->getX(), aCommandDTO->getY());
    }

}

void Worm::tryAttackVariablePower() {
    // si entra aca es porque dejo de presionar space_bar y ademas tengo un arma con disparo de potencia variable.
    if(typeCharge == MANY_CHARGE){
        if(armament.getWeaponCurrent() == BAZOOKA){
            attackWithBazooka();
        } // agregar aca los otros tipos de arma con potencia variable
        armament.putWeaponOnStandByAndUnarmed(); // luego de atacar con la bazoka pasamos el arma a standB y nos desarmamos
        this->typeCharge = NONE_CHARGE;
        attacked = true;
    }
}
bool Worm::thereAreProjectiles(){
    if(not attacked ){
        return false;
    }
    if(attacked and armament.weaponStandByLaunchesProjectiles()){
        return armament.thereAreProjectiles(); // pregunto si la arma en standBy (con la q dispare tiene algun projectil todavia).
    }
    return false;
}

bool Worm::isUnmoveAndNotExistsPojectiles() {
    bool unMovedOnABeam = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and (contatctsWithBeam > 0);
    bool unMovedOnAWorm = false;
    if(contatctsWithBeam == 0 and (contactsWithWorms > 0) ){ // si no esta sobre una viga pero esta sobre un gusano entonces esta inmobil.
        unMovedOnAWorm =  true;
    }
    // si esta cargando el arma tampoco debe acabar el turno asi que pedimos que sea de tipo de carga NONE_CHARGE.
    return ((unMovedOnABeam or unMovedOnAWorm) and (not thereAreProjectiles()) and (this->typeCharge == NONE_CHARGE)  );
}

void Worm::assigOnABeam() {
    contatctsWithBeam++;
}

void Worm::unAssingOnABeam(){
    contatctsWithBeam--;
}

void Worm::unAssignNextToAWorm() {
    contactsWithWorms--;
}

void Worm::assigNextToAWorm() {
    contactsWithWorms++;
}
