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
#include "../Weapons/WeaponsWorm/Mortar.h"


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
    iterationsForBatAttack = gameParameters.getAnimationIterations();
    positionInAir= std::make_pair(0.0f, 0.0f);
    hpInitialTurn = hp;
    contatctsWithBeam = 0;
    contactsWithWorms = 0;
    wasDestroyed = false;
    waitingToGetFocus = false;
    waitTime = gameParameters.getWaitTimeWeaponDefault();
    idWormCurrentPlay = VALUE_INITIAL_ID;
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
    if( aDamage >= this->hp){
        this->hp = 0.0;
        this->destroyBody();                // destruimos el body del gusano aca todo
    } else if (aDamage < this->hp){
        this->hp -=aDamage;
    }
    if(this->idWormCurrentPlay != idWorm){
        this->hpInitialTurn = hp;
    }
}

void Worm::giveExtraHP(const float &extraHP) {
    if( (this->hp + extraHP) <= gameParameters.getMaxHPWorm()){
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
    return hpInitialTurn > hp;
}

bool Worm::alreadyAttack() const{
    return attacked;
}

Direction Worm::getDirection() {
    return this->directionLook;
}

// DTOS.
WormDTO Worm::getWormDTO() const {
    TypeWeapon typeWeapon = NONE_WEAPON;
    if(idWormCurrentPlay == idWorm){
        typeWeapon = armament.getWeaponCurrent();
    }
    return WormDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                   gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()),
                   this->idPlayer, this->hp, this->directionLook, this->typeFocus, this->typeMov, typeWeapon );
}

WeaponSightDTO Worm::getWeaponSightDTO() {
    if(idWormCurrentPlay != idWorm){
        return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
    }
    return armament.getWeaponSightDTO(this->body->GetWorldCenter(), directionLook);
}

ProjectilesDTO Worm::getProjectilesDTO() {
    if(typeMov == ATTACKING_WITH_BAT or idWormCurrentPlay != idWorm){
         std::vector<ProjectileDTO> vecProjectileDTO;
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    ProjectilesDTO projectilesDto = armament.getProjectilesDTO(attacked);
    if(projectilesDto.getProjectilesDto().empty() and waitingToGetFocus and attacked){ // pregunto si ataco tambien para devolverme el focus.
        waitingToGetFocus = false;
        this->typeFocus = FOCUS;
    }
    return projectilesDto;
}

void Worm::activateFocus() {
    this->typeFocus = FOCUS;
    this->idWormCurrentPlay = this->idWorm;
}

void Worm::update() {
    if (this->isDestroyedBody() and not wasDestroyed) {
        aWorld->DestroyBody(this->getBody());
        this->wasDestroyed = true;
        return;
    } else if (idWorm != idWormCurrentPlay){
        return;
    }
    armament.tryCleanProjectiles(aWorld);
    armament.updateTime(attacked); // update para las armas en standby que esperan a exploar hacemos q pase el tiempo para ellas.
    if (this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) { // and not wasDestroyed ??
        if (this->typeMov == ATTACKING_WITH_BAT and iterationsForBatAttack > 0) {
            iterationsForBatAttack--;
        } else {
            this->typeMov = STANDING;
            if(iterationsForBatAttack == 0){
                iterationsForBatAttack = gameParameters.getAnimationIterations();
                armament.putWeaponOnStandByAndUnarmed(); // ya paso el frame del ataque con bate asi q lo desarmamos.
            }
        }
        armament.getWeaponOnStandBy(attacked);
    }
}


// weapons.- Attacks

void Worm::assignWeapon(const TypeWeapon& aTypeWeapon){
    if(typeFocus == NO_FOCUS){
        this->typeFocus = FOCUS;
    }
    if( not attacked and idWorm == idWormCurrentPlay){
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
    if(not armament.hasMunition() ){
        return;
    } else if(typeCharge == NONE_CHARGE){ // cargo por primera vez.
        typeCharge = MANY_CHARGE;
        reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
    } else if ( typeCharge == MANY_CHARGE) {
        reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
    } if(reachMaxImpulse){
        tryAttackVariablePower();
    }
}

void Worm::tryAttackVariablePower() {
    if(typeCharge == MANY_CHARGE){
        if(armament.getWeaponCurrent() == BAZOOKA){
            attackWithBazooka();
        } else if (armament.isAGrenade()){
            attackWithGrenade();
        } else if (armament.getWeaponCurrent() == MORTAR){
            attackWithMortar();
        }
        this->endAttack();
        this->typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
        this->typeCharge = NONE_CHARGE;
    }
}

void Worm::attackWithGrenade(){
    armament.attackWithGrenade(this->getBody()->GetWorldCenter(), directionLook, typeFocus, waitTime, aWorld);
}

void Worm::attackWithMortar(){
    Mortar *mortar = (Mortar*) armament.getWeaponCurrentPtr();
    mortar->shootProjectile(aWorld, this->getBody()->GetWorldCenter(), directionLook, typeFocus);
}

void Worm::attack(std::unique_ptr<CommandDTO> &aCommand) {
    bool couldAttack = true; // para todas las armas sin municiones, si usa un arma q aplca municiones este valor puede cambiar. sino tiene municiones.
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    } else if ( this->armament.getWeaponCurrentPtr()->hasVariablePower()){ // en un futuro pregunta si tiene un arma con potencia variable.
        this->chargeWeaponWithVariablePower();
        return;
    } else if( this->armament.getWeaponCurrent() == BASEBALL_BAT){
        this->attackWithBat();
    } else if (this->armament.getWeaponCurrent() == TELEPORT){      //Si hace un teleport y no tepea bien igual cuenta como si hubiera atacado.
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
}

void Worm::teleportWorm(const int &posXTeleport, const int &posYTeleport){
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport, aWorld);
    this->waitingToGetFocus = false;
    this->typeFocus = FOCUS;
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
    idWormCurrentPlay = VALUE_INITIAL_ID;
}

void Worm::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft, size_t idCurrentWorm) {
    this->idWormCurrentPlay = idCurrentWorm;
    if(timeLeft <= 0 or this->idWorm != idWormCurrentPlay){ // no le pongo el and not wasDestroyed porque nunca sera el turno del worm destruido.
        return;
    }
    std::cout << "Se recibe el comando " << aCommandDTO->getTypeCommand() << "\n";
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
        typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BAZOOKA){
        this->assignWeapon(BAZOOKA);
    }  else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_DYNAMITE){
        this->assignWeapon(DYNAMITE_HOLDER);
    }  else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_GREEN_GRENADE){
        this->assignWeapon(GREEN_GRENADE);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_BANANA){
        this->assignWeapon(BANANA);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_HOLY_GRENADE){
        this->assignWeapon(HOLY_GRENADE);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_RED_GRENADE){
        this->assignWeapon(RED_GRENADE);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_MORTAR){
        this->assignWeapon(MORTAR);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::SELECT_AIR_ATTACK ){
        this->assignWeapon(AIR_ATTACK);
        typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
    }
    // execute an attack of a weapon
    else if (aCommandDTO->getTypeCommand() == TypeCommand::FIRE_CMD){
        this->attack(aCommandDTO);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::TELEPORT_MOVE){
        this->attack(aCommandDTO);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::AIR_ATTACK_POINT ){
        this->attack(aCommandDTO);
    }

}

bool Worm::thereAreProjectiles(){
    if (attacked and armament.weaponStandByLaunchesProjectiles()) {
        return armament.thereAreProjectiles();
    }
    return false;
}

bool Worm::isStopTheWorm() const {
    bool unMovedOnABeam = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and (contatctsWithBeam > 0);
    //bool unMovedOnEdge = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and (contactsWithEdge > 0);
    bool unMovedOnAWorm = false;
    if(contatctsWithBeam == 0 and (contactsWithWorms > 0) ){ // si no esta sobre una viga pero esta sobre un gusano entonces esta inmobil.
        unMovedOnAWorm =  true;
    }
    return (unMovedOnAWorm or unMovedOnABeam);
}

bool Worm::isUnmoveAndNotExistsPojectiles() {
    if(this->wasDestroyedWorm()){ // si el gusano fue destruido no existe movimiento ni proyectiles q pueda lanzar.
        return true;
    }
    // si esta cargando el arma tampoco debe acabar el turno asi que pedimos que sea de tipo de carga NONE_CHARGE.
    return ( isStopTheWorm() and (not thereAreProjectiles()) and (this->typeCharge == NONE_CHARGE)  );
}

void Worm::setHP(const float &aNewHP) {
    this->hp = aNewHP;
}

void Worm::setWaitTime(const int &aWaitTIme) {
    this->waitTime = aWaitTIme;
}


void Worm::assignTypeFocus(const TypeFocus &focus) {
    this->typeFocus = focus;
}

bool Worm::hasTheTeleport() const {
    return armament.getWeaponCurrent() == TELEPORT;
}


