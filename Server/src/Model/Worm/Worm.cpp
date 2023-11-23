//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include <iostream>
#include "Worm.h"
#include "../../../GameParameters/GameParameters.h"
#include "../Weapons/WeaponsWorm/AirAttackDetonator.h"
#include "../Weapons/WeaponsWorm/DynamiteHolder.h"
#include "../Weapons/WeaponsWorm/GrenadeHolder.h"

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
    onInclinedBeam = false;         // posiblemente cambiar por un size_t en un futuro pendiente @todo
    attacked = false;
    typeCharge = NONE_CHARGE;
    iterationsForBatAttack = gameParameters.getBatIterations();
    positionInAir= std::make_pair(0.0f, 0.0f);
    hpInitialTurn = hp;
    contatctsWithBeam = 0;
    contactsWithWorms = 0;
    wasDestroyed = false;
    waitingToGetFocus = false;
    waitTime = 5;
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
void Worm::assigOnABeam() {
    contatctsWithBeam++;
}

void Worm::unAssingOnABeam(){
    contatctsWithBeam--;
}

void Worm::aContactWithEdge(){
    contactsWithEdge++;
}
void Worm::lessContactWithEdge(){
    contactsWithEdge--;
}

void Worm::unAssignNextToAWorm() {
    contactsWithWorms--;
}

void Worm::assigNextToAWorm() {
    contactsWithWorms++;
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
    this->body->CreateFixture(&defFixtureWorm);
    this->aWorld = world;
}

// for worm moves.

void Worm::jump(const TypeJump& typeJump){
    if( contactsWithWorms == 0  and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ){
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
        float impulseX = body->GetMass() * initialSpeed * cos(angleTita), impulseY = body->GetMass() * initialSpeed * sin(angleTita);

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
    if( contactsWithWorms == 0  and this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) {
        this->typeMov = MoveWorm::WALKING;
        directionLook = aDirection;
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * (gameParameters.getGravity() * -1); // aceleracion es la froz = u.N , las masas se cancelan queda mu * g.
        float impulseX = body->GetMass() * sqrt(2.0f * acceleration * dragSpeed), impulseY = 0.0;               // la velocidad la sacamos como 2 * aceleracion * distancia.
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
        b2Vec2 impulseSpeed(impulseX, impulseY); //  por la gravedad
        body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
    }
}

// borrar esto @todo
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

void Worm::walkWorm(const Direction& aDiretion){
    if( armament.isUnarmed() ){
        walk(aDiretion);
    } else if ( not armament.isUnarmed() and this->directionLook == aDiretion ){
        armament.putWeaponOnStandByAndUnarmed();
        walk(aDiretion);
    } else{
        this->directionLook = aDiretion;
    }
}

// polimorfismo aca obtenemos el arma q tengamos actualmente e incrmentamos el angle si algunoas armas haran algo otras no.
// this->armament.getWeaponCurrentPtr() es remeplazada por el arma actual por ej bat y llama al increasAngle de bat.
void Worm::changeAngle(const Direction& direction){
    if(armament.isUnarmed()){
        return;
    }
    if(direction== UP){
        this->armament.getWeaponCurrentPtr()->increaseAngle();
    } else if ( direction == DOWN){
        this->armament.getWeaponCurrentPtr()->decreaseAngle();
    }
}

void Worm::takeDamage(const float &aDamage){
    std::cout << "PlayerID: :" << idPlayer << "Con WormID: " << idWorm << " recibe daño de " <<  aDamage << "\n";
    if( aDamage >= this->hp){
        this->hp = 0.0;
        this->destroyBody();                // destruimos el body del gusano aca todo
    } else if (aDamage < this->hp){
        this->hp -=aDamage;
    }
    if(this->typeFocus == NO_FOCUS){
        this->hpInitialTurn = hp;
    }
}

void Worm::giveExtraHP(const float &extraHP) {
    if( (this->hp + extraHP) <= 200){
        this->hp +=extraHP;
    }
}

void Worm::giveExtraMunition(const size_t &extraMunition) {
    this->armament.giveExtraMunition(extraMunition);
}

//getters

float Worm::getHP() const {
    return this->hp;
}
bool Worm::wasDestroyedWorm() const{
    return this->wasDestroyed;
}

bool Worm::wasDamaged() const{
    return hpInitialTurn != hp;
}

bool Worm::alreadyAttack() const{
    return attacked;
}

Direction Worm::getDirection() {
    return this->directionLook;
}

// DTOS.
WormDTO Worm::getWormDTO() const {
    TypeWeapon typeWeapon = armament.getWeaponCurrent();
    if(this->typeFocus == NO_FOCUS){
        typeWeapon = NONE_WEAPON;
    }
    return WormDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                   gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                   this->idPlayer, this->hp, this->directionLook, this->typeFocus, this->typeMov, typeWeapon );
}

WeaponSightDTO Worm::getWeaponSightDTO() {
    if(typeFocus == NO_FOCUS){
        return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
    }
    return armament.getWeaponSightDTO(this->body->GetWorldCenter(), directionLook);
}

ProjectilesDTO Worm::getProjectilesDTO() {
    if(typeMov == ATTACKING_WITH_BAT){
         std::vector<ProjectileDTO> vecProjectileDTO;
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    ProjectilesDTO projectilesDto = armament.getProjectilesDTO(attacked);
    if(projectilesDto.getProjectilesDto().empty() and waitingToGetFocus ){
        this->typeFocus = FOCUS;
    }
    return projectilesDto;
}

void Worm::activateFocus() {
    this->typeFocus = TypeFocus::FOCUS;
}

void Worm::update() {
    armament.tryCleanProjectiles(aWorld);
    armament.updateTime(attacked); // update para las armas en standby que esperan a exploar hacemos q pase el tiempo para ellas.
    if (this->isDestroyedBody() and not wasDestroyed) {     // Si el gusano fue destrouido lo destruimos del mundoo. Ademas no lo actualizamos;
        aWorld->DestroyBody(this->getBody());
        this->wasDestroyed = true;
        return;
    }
    else if (this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and this->typeFocus == FOCUS and not wasDestroyed) {
        if (this->typeMov == ATTACKING_WITH_BAT and iterationsForBatAttack > 0) {
            std::cout << "Atacand con el bate\n";
            iterationsForBatAttack--;
        } else {
            this->typeMov = STANDING;
            if(iterationsForBatAttack == 0){
                iterationsForBatAttack = gameParameters.getBatIterations();
                armament.putWeaponOnStandByAndUnarmed(); // ya paso el frame del ataque con bate asi q lo desarmamos.
            }
        }
        armament.getWeaponOnStandBy(attacked);
    }
}


// weapons.- Attacks

void Worm::assignWeapon(const TypeWeapon& aTypeWeapon){
    if( not attacked and this->typeFocus == FOCUS){ // SOLO asigno un arma si no ataque y si tengo el focus.
        armament.assignWeapon(aTypeWeapon, this->directionLook);
    }
}

// Desarmo el arma que tengo y seteo que ya ataque
void Worm::endAttack(){
    armament.putWeaponOnStandByAndUnarmed();
    attacked = true;
}

void Worm::chargeWeaponWithVariablePower(){
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

void Worm::tryAttackVariablePower() {
    // si entra aca es porque dejo de presionar space_bar y ademas tengo un arma con disparo de potencia variable.
    if(typeCharge == MANY_CHARGE){
        if(armament.getWeaponCurrent() == BAZOOKA){
            attackWithBazooka();
        } else if (armament.getWeaponCurrent() == GREEN_GRENADE){
            GrenadeHolder* grenadeHolder =  (GrenadeHolder*) armament.getWeaponCurrentPtr();
            grenadeHolder->attack(GREEN_GRENADE, this->getBody()->GetWorldCenter(), directionLook, typeFocus,
                                  waitTime, aWorld);
            this->typeFocus = NO_FOCUS;
            waitingToGetFocus = true;
        }

        // agregar aca los otros tipos de arma con potencia variable
        // luego de atacar con la bazoka o cualquier weapo con variable power pasamos el arma a standB y nos desarmamos
        this->endAttack();
        this->typeCharge = NONE_CHARGE;
    }
}

void Worm::attack(std::unique_ptr<CommandDTO> &aCommand) {
    bool couldAttack = true; // para todas las armas sin municiones, si usa un arma q aplca municiones este valor puede cambiar. sino tiene municiones.
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    } else if ( this->armament.getWeaponCurrentPtr()->hasVariablePower()){ // en un futuro pregunta si tiene un arma con potencia variable.
        this->chargeWeaponWithVariablePower();
        return;
    } else if( this->armament.getWeaponCurrent() == BASEBALL_BAT){ // armas abajo sin potencia variable.
        this->attackWithBat();
    } else if (this->armament.getWeaponCurrent() == TELEPORT){
        this->teleportWorm(aCommand->getX(), aCommand->getY());
    } else if ( this->armament.getWeaponCurrent() == AIR_ATTACK){
        couldAttack = this->attackWithAirAttack(aCommand->getX());
    } else if (this->armament.getWeaponCurrent() == DYNAMITE_HOLDER){
        couldAttack = this->attackWithDynamiteHolder();
    }

    if(couldAttack){
        this->endAttack();
    }

}

// WEAPONS without potencia variable
void Worm::attackWithBat(){
    this->typeMov = ATTACKING_WITH_BAT;
    Bat* aBat = (Bat*) this->armament.getWeaponCurrentPtr();
    aBat->searchWormAndAttack(aWorld, this->body->GetWorldCenter(), directionLook);
}

void Worm::attackWithBazooka() {
    Bazooka *bazooka = (Bazooka *) armament.getWeaponCurrentPtr();
    bazooka->shootProjectile(aWorld, this->getBody()->GetWorldCenter(), directionLook, typeFocus);
    this->typeFocus = NO_FOCUS; // nos sacamos el focus y disparamos el misil. hasta q explote.
    waitingToGetFocus = true;
}

void Worm::teleportWorm(const int &posXTeleport, const int &posYTeleport){
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport, aWorld);
}

bool Worm::attackWithAirAttack(const int &posXAttack) {
    if(not this->armament.hasMunition()){
        return false;
    }
    AirAttackDetonator* airAttackDetonator = (AirAttackDetonator*) this->armament.getWeaponCurrentPtr();
    airAttackDetonator->detonate(posXAttack, aWorld, this->typeFocus);
    this->typeFocus = NO_FOCUS; // nos sacamos el focus y disparamos el misil. hasta q explote.
    waitingToGetFocus = true;
    return true;
}

bool Worm::attackWithDynamiteHolder() {
    if(not this->armament.hasMunition()){
        return false;
    }
    DynamiteHolder* dynamiteHolder = (DynamiteHolder*) armament.getWeaponCurrentPtr();
    dynamiteHolder->placeDynamite(waitTime, body->GetWorldCenter(), directionLook, aWorld, typeFocus);
    return true;
}


void Worm::endTurn() {
    typeFocus = NO_FOCUS;
    typeMov = STANDING;
    attacked = false;
    waitingToGetFocus = false;
    armament.endTurn();
    hpInitialTurn = hp;
}

void Worm::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft, size_t idCurrentWorm) {
    if(timeLeft <= 0 or this->idWorm != idCurrentWorm){ // no le pongo el and not wasDestroyed porque nunca sera el turno del worm destruido.
        return;
    }
    // movs, up/down angles, jumps
    if(aCommandDTO->getTypeCommand() == TypeCommand::LEFT_CMD ){
        this->walkWorm(LEFT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::RIGHT_CMD ){
        this->walkWorm(RIGHT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::UP_CMD){
        this->changeAngle(UP);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::DOWN_CMD){
        this->changeAngle(DOWN);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_BACK_CMD){
        this->jump(JUMP_BACKWARDS);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::JUMP_FORWARD_CMD){
        this->jump(JUMP_FORWARDS);
    }
    // select weapons
    else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BAT){
        this->assignWeapon(BASEBALL_BAT); // BASEBALL_BAT
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_TELEPORT){
        this->assignWeapon(TELEPORT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BAZOOKA){
        this->assignWeapon(BAZOOKA);
    }  else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_DYNAMITE){
        this->assignWeapon(DYNAMITE_HOLDER);
    }  else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_GREEN_GRENADE){
        this->assignWeapon(GREEN_GRENADE);
    }
        // execute an attack of a weapon
    else if (aCommandDTO->getTypeCommand() == TypeCommand::FIRE_CMD){
        this->attack(aCommandDTO);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::TELEPORT_MOVE){
        this->attack(aCommandDTO);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_AIR_ATTACK ){
        this->assignWeapon(AIR_ATTACK);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::AIR_ATTACK_POINT ){
        this->attack(aCommandDTO);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::COUNTDOWN){
        std::cout << "Se recibe  CD:"  << aCommandDTO->getX() << "\n";
        this->waitTime = aCommandDTO->getX();
    }
}

bool Worm::thereAreProjectiles(){
    if (attacked and armament.weaponStandByLaunchesProjectiles()) {
        return armament.thereAreProjectiles(); // pregunto si la arma en standBy (con la q dispare tiene algun projectil todavia).
    }
    return false;
}

bool Worm::isUnmoveAndNotExistsPojectiles() {
    if(this->wasDestroyedWorm()){ // si el gusano fue destruido no existe movimiento ni proyectiles q pueda lanzar.
        return true;
    }
    bool unMovedOnABeam = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and (contatctsWithBeam > 0);
    //bool unMovedOnEdge = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and (contactsWithEdge > 0);
    bool unMovedOnAWorm = false;
    if(contatctsWithBeam == 0 and (contactsWithWorms > 0) ){ // si no esta sobre una viga pero esta sobre un gusano entonces esta inmobil.
        unMovedOnAWorm =  true;
    }
    // si esta cargando el arma tampoco debe acabar el turno asi que pedimos que sea de tipo de carga NONE_CHARGE.
    return ((unMovedOnABeam or unMovedOnAWorm ) and (not thereAreProjectiles()) and (this->typeCharge == NONE_CHARGE)  );
}

void Worm::setHP(const float &aNewHP) {
    this->hp = aNewHP;
}


