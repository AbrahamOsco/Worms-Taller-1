//
// Created by abraham on 28/10/23.
//

#include <cstddef>
#include <vector>
#include <iostream>
#include "Worm.h"
#include "../../../GameParameters/GameParameters.h"
#include "../Weapons/WeaponsWorm/AirAttackDetonator.h"
#include "../Weapons/WeaponsWorm/DynamiteHolder.h"
#include "../Weapons/WeaponsWorm/GrenadeHolder.h"
#include "../Weapons/WeaponsWorm/Mortar.h"


Worm::Worm(const size_t &idWorm, const size_t &idPlayer,  const float &posIniX, const float &posIniY,
        const GameParameters &gameParameter, Armament& armament) : GameObject(ENTITY_WORM), idWorm(idWorm),
        idPlayer(idPlayer), positionInitialX(posIniX), positionInitialY(posIniY), gameParameters(gameParameter),
        aWorld(nullptr), armament(armament), numberContacts(0), contactsWithEdge(0) {
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
    positionInAir = std::make_pair(0.0f, 0.0f);
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

std::pair<float, float>  Worm::getPositionAir() const {
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

void Worm::unAssingOnABeam() {
    contatctsWithBeam--;
}

void Worm::aContactWithEdge() {
    contactsWithEdge++;
}
void Worm::lessContactWithEdge() {
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

void Worm::jump(const TypeJump& typeJump) {
    if ( contactsWithWorms == 0  && this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) {
        armament.putWeaponOnStandByAndUnarmed();  // guardamos el arma actual y nos desarmamos
        float distanceX = distancesJumpForward.first;
        float distanceY = distancesJumpForward.second;
        if (typeJump == JUMP_BACKWARDS) {
            distanceX = distancesJumpBack.first;
            distanceY = distancesJumpBack.second;
        }
        this->typeMov = JUMPING;
        float angleTita = atan(4.0f * distanceY / distanceX);
        float initialSpeed = sqrt(distanceX * (gameParameters.getGravity() * -1) / (sin(2 * angleTita)));
        float impulseX = body->GetMass() * initialSpeed * cos(angleTita), impulseY = body->GetMass() *
            initialSpeed * sin(angleTita);

        if (typeJump == JUMP_BACKWARDS) {
            if (directionLook == RIGHT) {
                impulseX = -impulseX;
                directionLook = LEFT;
            } else if (directionLook == LEFT) {
                directionLook = RIGHT;
            }
        } else if (typeJump == JUMP_FORWARDS) {
            if (directionLook == LEFT) {
                impulseX = -impulseX;
            }
        }
        b2Vec2 impulse(impulseX, impulseY);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }
}

void Worm::walk(Direction aDirection) {
    if ( contactsWithWorms == 0  && this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) ) {
        this->typeMov = MoveWorm::WALKING;
        directionLook = aDirection;
        float acceleration = getBody()->GetFixtureList()[0].GetFriction() * (gameParameters.getGravity() * -1);
        float impulseX = body->GetMass() * sqrt(2.0f * acceleration * dragSpeed), impulseY = 0.0;
        if (directionLook == Direction::LEFT) {
            impulseX *=-1;
        }
        if (onInclinedBeam) {
            impulseX *= gameParameters.getWormImpulseFactoScalingDown();
            if (directionLook == Direction::RIGHT) {
                impulseX *= gameParameters.getWormImpulseFactorClimbingUp();
                impulseY = impulseX;
            } else {
                impulseY = impulseX*-1;
            }
        }
        b2Vec2 impulseSpeed(impulseX, impulseY);
        body->ApplyLinearImpulse(impulseSpeed, body->GetWorldCenter(), true);
    }
}

void Worm::walkWorm(const Direction& aDiretion) {
    if ( armament.isUnarmed() ) {
        walk(aDiretion);
    } else if ( !armament.isUnarmed() && this->directionLook == aDiretion ) {
        armament.putWeaponOnStandByAndUnarmed();
        walk(aDiretion);
    } else {
        this->directionLook = aDiretion;
    }
}

void Worm::changeAngle(const Direction& direction) {
    if (armament.isUnarmed()) {
        return;
    }
    if (direction== UP) {
        this->armament.getWeaponCurrentPtr()->increaseAngle();
    } else if (direction == DOWN) {
        this->armament.getWeaponCurrentPtr()->decreaseAngle();
    }
}

void Worm::takeDamage(const float &aDamage) {
    if (aDamage >= this->hp) {
        this->hp = 0.0;
        this->destroyBody();
    } else if (aDamage < this->hp) {
        this->hp -= aDamage;
    }
    if (this->idWormCurrentPlay != idWorm) {
        this->hpInitialTurn = hp;
    }
}

void Worm::giveExtraHP(const float &extraHP) {
    if ((this->hp + extraHP) <= gameParameters.getMaxHPWorm()) {
        if (this->hp == hpInitialTurn) {
            this->hp +=extraHP;
            hpInitialTurn = this->hp;
        }
    }
}

void Worm::giveExtraMunition(const size_t &extraMunition) {
    this->armament.giveExtraMunition(extraMunition);
}

// getters

float Worm::getHP() const {
    return this->hp;
}
bool Worm::wasDestroyedWorm() const {
    return this->wasDestroyed;
}

bool Worm::wasDamaged() const {
    return hpInitialTurn > hp;
}

bool Worm::alreadyAttack() const {
    return attacked;
}

Direction Worm::getDirection() {
    return this->directionLook;
}

// DTOS.
WormDTO Worm::getWormDTO() const {
    TypeWeapon typeWeapon = NONE_WEAPON;
    if (idWormCurrentPlay == idWorm) {
        typeWeapon = armament.getWeaponCurrent();
    }
    return WormDTO(this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                   gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y *
                   gameParameters.getPositionAdjustment()), this->idPlayer, this->hp, this->directionLook,
                   this->typeFocus, this->typeMov, typeWeapon);
}

WeaponSightDTO Worm::getWeaponSightDTO() {
    if (idWormCurrentPlay != idWorm) {
        return WeaponSightDTO(NO_SHOW_SIGHT, 0, 0);
    }
    return armament.getWeaponSightDTO(this->body->GetWorldCenter(), directionLook);
}

ProjectilesDTO Worm::getProjectilesDTO() {
    if (typeMov == ATTACKING_WITH_BAT || idWormCurrentPlay != idWorm) {
         std::vector<ProjectileDTO> vecProjectileDTO;
        return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
    }
    ProjectilesDTO projectilesDto = armament.getProjectilesDTO(attacked);
    if (projectilesDto.getProjectilesDto().empty() && waitingToGetFocus && attacked) {
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
    if (this->isDestroyedBody() && !wasDestroyed) {
        aWorld->DestroyBody(this->getBody());
        this->wasDestroyed = true;
        return;
    } else if (idWorm != idWormCurrentPlay) {
        return;
    }
    armament.tryCleanProjectiles(aWorld);
    armament.updateTime(attacked);
    if (this->body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f)) {  // and not wasDestroyed ??
        if (this->typeMov == ATTACKING_WITH_BAT && iterationsForBatAttack > 0) {
            iterationsForBatAttack--;
        } else {
            this->typeMov = STANDING;
            if (iterationsForBatAttack == 0) {
                iterationsForBatAttack = gameParameters.getAnimationIterations();
                armament.putWeaponOnStandByAndUnarmed();
            }
        }
        armament.getWeaponOnStandBy(attacked);
    }
}


// weapons.- Attacks

void Worm::assignWeapon(const TypeWeapon& aTypeWeapon) {
    if (typeFocus == NO_FOCUS) {
        this->typeFocus = FOCUS;
    }
    if (!attacked && idWorm == idWormCurrentPlay) {
        armament.assignWeapon(aTypeWeapon, this->directionLook);
    }
}

void Worm::endAttack() {
    armament.putWeaponOnStandByAndUnarmed();
    attacked = true;
}

void Worm::chargeWeaponWithVariablePower() {
    bool reachMaxImpulse = false;
    if (!armament.hasMunition()) {
        return;
    } else if (typeCharge == NONE_CHARGE) {
        typeCharge = MANY_CHARGE;
        reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
    } else if (typeCharge == MANY_CHARGE) {
        reachMaxImpulse = this->armament.getWeaponCurrentPtr()->increaseImpulse();
    }
    if (reachMaxImpulse) {
        tryAttackVariablePower();
    }
}

void Worm::tryAttackVariablePower() {
    if (typeCharge == MANY_CHARGE) {
        if (armament.getWeaponCurrent() == BAZOOKA) {
            attackWithBazooka();
        } else if (armament.isAGrenade()) {
            attackWithGrenade();
        } else if (armament.getWeaponCurrent() == MORTAR) {
            attackWithMortar();
        }
        this->endAttack();
        this->typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
        this->typeCharge = NONE_CHARGE;
    }
}

void Worm::attackWithGrenade() {
    armament.attackWithGrenade(this->getBody()->GetWorldCenter(), directionLook, typeFocus, waitTime, aWorld);
}

void Worm::attackWithMortar() {
    Mortar *mortar = (Mortar*) armament.getWeaponCurrentPtr();
    mortar->shootProjectile(aWorld, this->getBody()->GetWorldCenter(), directionLook, typeFocus);
}

void Worm::attack(const CommandDTO &aCommand) {
    bool couldAttack = true;
    if (this->armament.getWeaponCurrent() == NONE_WEAPON || attacked) {
        return;
    } else if (this->armament.getWeaponCurrentPtr()->hasVariablePower()) {
        // en un futuro pregunta si tiene un arma con potencia variable.
        this->chargeWeaponWithVariablePower();
        return;
    } else if (this->armament.getWeaponCurrent() == BASEBALL_BAT) {
        this->attackWithBat();
    } else if (this->armament.getWeaponCurrent() == TELEPORT) {
        // Si hace un teleport y no tepea bien igual cuenta como si hubiera atacado.
        this->teleportWorm(aCommand.getX(), aCommand.getY());
    } else if (this->armament.getWeaponCurrent() == AIR_ATTACK) {
        couldAttack = this->attackWithAirAttack(aCommand.getX());
    } else if (this->armament.getWeaponCurrent() == DYNAMITE_HOLDER) {
        couldAttack = this->attackWithDynamiteHolder();
    }
    if (couldAttack) {
        this->endAttack();
    }
}


// WEAPONS without potencia variable
void Worm::attackWithBat() {
    this->typeMov = ATTACKING_WITH_BAT;
    Bat* aBat = (Bat*) this->armament.getWeaponCurrentPtr();
    aBat->searchWormAndAttack(aWorld, this->body->GetWorldCenter(), directionLook);
}

void Worm::attackWithBazooka() {
    Bazooka *bazooka = (Bazooka *) armament.getWeaponCurrentPtr();
    bazooka->shootProjectile(aWorld, this->getBody()->GetWorldCenter(), directionLook, typeFocus);
}

void Worm::teleportWorm(const int &posXTeleport, const int &posYTeleport) {
    Teleport* teleport = (Teleport*) this->armament.getWeaponCurrentPtr();
    teleport->teleportIn(getBody(), posXTeleport, posYTeleport, aWorld);
    this->waitingToGetFocus = false;
    this->typeFocus = FOCUS;
}

bool Worm::attackWithAirAttack(const int &posXAttack) {
    if (!this->armament.hasMunition()) {
        return false;
    }
    AirAttackDetonator* airAttackDetonator = (AirAttackDetonator*) this->armament.getWeaponCurrentPtr();
    airAttackDetonator->detonate(posXAttack, aWorld, FOCUS);
    this->typeFocus = NO_FOCUS;  // nos sacamos el focus y disparamos el misil. hasta q explote.
    waitingToGetFocus = true;
    return true;
}

bool Worm::attackWithDynamiteHolder() {
    if (!this->armament.hasMunition()) {
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

void Worm::execute(const CommandDTO &aCommandDTO, const int &timeLeft, const size_t &idCurrentWorm) {
    this->idWormCurrentPlay = idCurrentWorm;
    if (timeLeft <= 0 || this->idWorm != idWormCurrentPlay) {
        return;
    }
    if (aCommandDTO.getTypeCommand() == TypeCommand::LEFT_CMD) {
        this->walkWorm(LEFT);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::RIGHT_CMD) {
        this->walkWorm(RIGHT);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::UP_CMD) {
        this->changeAngle(UP);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::DOWN_CMD) {
        this->changeAngle(DOWN);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::JUMP_BACK_CMD) {
        this->jump(JUMP_BACKWARDS);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::JUMP_FORWARD_CMD) {
        this->jump(JUMP_FORWARDS);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_BAT) {
        this->assignWeapon(BASEBALL_BAT);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_TELEPORT) {
        this->assignWeapon(TELEPORT);
        typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_BAZOOKA) {
        this->assignWeapon(BAZOOKA);
    }  else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_DYNAMITE) {
        this->assignWeapon(DYNAMITE_HOLDER);
    }  else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_GREEN_GRENADE) {
        this->assignWeapon(GREEN_GRENADE);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_BANANA) {
        this->assignWeapon(BANANA);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_HOLY_GRENADE) {
        this->assignWeapon(HOLY_GRENADE);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_RED_GRENADE) {
        this->assignWeapon(RED_GRENADE);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_MORTAR) {
        this->assignWeapon(MORTAR);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::SELECT_AIR_ATTACK) {
        this->assignWeapon(AIR_ATTACK);
        typeFocus = NO_FOCUS;
        waitingToGetFocus = true;
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::FIRE_CMD) {  // execute an attack of a weapon
        this->attack(aCommandDTO);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::TELEPORT_MOVE) {
        this->attack(aCommandDTO);
    } else if (aCommandDTO.getTypeCommand() == TypeCommand::AIR_ATTACK_POINT) {
        this->attack(aCommandDTO);
    }
}

bool Worm::thereAreProjectiles() {
    if (attacked && armament.weaponStandByLaunchesProjectiles()) {
        return armament.thereAreProjectiles();
    }
    return false;
}

bool Worm::isStopTheWorm() const {
    bool unMovedOnABeam = body->GetLinearVelocity() == b2Vec2(0.0f, 0.0f) && (contatctsWithBeam > 0);
    bool unMovedOnAWorm = false;
    if (contatctsWithBeam == 0 && (contactsWithWorms > 0)) {
        unMovedOnAWorm =  true;
    }
    return (unMovedOnAWorm || unMovedOnABeam);
}

bool Worm::isUnmoveAndNotExistsPojectiles() {
    if (this->wasDestroyedWorm()) {
        return true;
    }
    return ( isStopTheWorm() && (!thereAreProjectiles()) && (this->typeCharge == NONE_CHARGE)  );
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

bool Worm::hasTheAirAttack() const {
    return armament.getWeaponCurrent() == AIR_ATTACK;
}

TypeFocus Worm::getTypeFocus() const {
    return this->typeFocus;
}
