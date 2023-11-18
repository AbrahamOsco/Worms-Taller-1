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
    onInclinedBeam = false;         // posiblemente cambiar por un size_t en un futuro pendiente @todo
    attacked = false;
    typeCharge = NONE_CHARGE;
    iterationsForBatAttack = gameParameters.getBatIterations();
    positionInAir= std::make_pair(0.0f, 0.0f);
    hpInitialTurn = hp;
    contatctsWithBeam = 0;
    contactsWithWorms = 0;
    wasDestroyed = false;
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

void Worm::upWorm() {
    if(armament.isUnarmed()){
        return;
    }
    // polimorfismo aca obtenemos el arma q tengamos actualmente e incrmentamos el angle si algunoas armas haran algo otras no.
    // this->armament.getWeaponCurrentPtr() es remeplazada por el arma actual por ej bat y llama al increasAngle de bat.
    this->armament.getWeaponCurrentPtr()->increaseAngle();
}

void Worm::downWorm() {
    if(armament.isUnarmed()){
        return;
    }
    this->armament.getWeaponCurrentPtr()->decreaseAngle();
}

//getters

float Worm::getHP() const {
    return this->hp;
}
bool Worm::wasDestroyedWorm() const{
    return this->wasDestroyed;
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
    return armament.getProjectilesDTO(attacked);
}

void Worm::activateFocus() {
    this->typeFocus = TypeFocusWorm::FOCUS;
}

void Worm::update() {
    if (this->isDestroyedBody() and not wasDestroyed) {     // Si el gusano fue destrouido lo destruimos del mundoo. Ademas no lo actualizamos;
        aWorld->DestroyBody(this->getBody());
        this->wasDestroyed = true;
        return;
    }
    else if (this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) and this->typeFocus == FOCUS and not wasDestroyed) {
        if (this->typeMov == ATTACKING_WITH_BAT and
            iterationsForBatAttack > 0) {  // el ATTACKING_WITH_BAT ES SOLO PARA BATE asi q no hay problemas.
            iterationsForBatAttack--;
        } else if (this->typeMov == ATTACKING_WITH_BAT and iterationsForBatAttack == 0) {
            iterationsForBatAttack = gameParameters.getBatIterations();
            this->typeMov = STANDING;
            armament.putWeaponOnStandByAndUnarmed(); // ya paso el frame del ataque con bate asi q lo desarmamos.
        } else {
            this->typeMov = STANDING;
        }
        // @todo creo q luego de disparar volvemos a tener todo armaCurrent en none.
        armament.getWeaponOnStandBy(attacked);
    }
    if (attacked and this->typeFocus == FOCUS and not wasDestroyed) {
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
        armament.putWeaponOnStandByAndUnarmed(); // luego de atacar con la bazoka pasamos el arma a standB y nos desarmamos
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

b2World* Worm::getWorld(){
    return this->aWorld;
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

void Worm::teleportWorm(const int &posXTeleport, const int &posYTeleport){
    if(this->armament.getWeaponCurrent() == NONE_WEAPON or attacked){
        return;
    }
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport, aWorld);
    armament.putWeaponOnStandByAndUnarmed(); // luego de atacar con la bazoka pasamos el arma a standB y nos desarmamos
    attacked = true;
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

void Worm::execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft, size_t idCurrentWorm) {
    if(timeLeft <= 0 or this->idWorm != idCurrentWorm){ // no le pongo el and not wasDestroyed porque nunca sera el turno del worm destruido.
        return;
    }
    if(aCommandDTO->getTypeCommand() == TypeCommand::LEFT_CMD ){
        this->walkWorm(LEFT);
    } else if (aCommandDTO->getTypeCommand() == TypeCommand::RIGHT_CMD ){
        this->walkWorm(RIGHT);
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
