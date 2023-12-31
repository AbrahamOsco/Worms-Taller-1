//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include <memory>
#include <utility>
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"
#include "../../../../Common/DTO/WormDTO.h"
#include "../../../GameParameters/GameParameters.h"
#include "../../../../Common/DTO/WeaponSightDTO.h"
#include "../Weapons/Armament/Armament.h"
#include "../Weapons/WeaponsWorm/Teleport.h"
#include "../Weapons/WeaponsWorm/Bat.h"
#include "../Weapons/WeaponsWorm/Bazooka.h"
#include "../../../../Common/DTO/CommandDTO.h"
#define VALUE_INITIAL_ID 1000

enum TypeJump{
    JUMP_BACKWARDS, JUMP_FORWARDS
};
enum TypeCharge{
    NONE_CHARGE, MANY_CHARGE
};


class Worm : public GameObject {
    size_t idWorm;
    size_t idPlayer;
    Direction directionLook;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;
    std::pair<float, float> distancesJumpForward;
    std::pair<float, float> distancesJumpBack;
    size_t numberContacts;
    TypeFocus typeFocus;
    MoveWorm typeMov;
    const GameParameters& gameParameters;
    b2World* aWorld;
    Armament& armament;
    size_t contatctsWithBeam;
    size_t contactsWithEdge;
    bool onInclinedBeam;
    size_t contactsWithWorms;
    bool attacked;
    size_t iterationsForBatAttack;
    std::pair<float, float> positionInAir;
    TypeCharge typeCharge;
    float hpInitialTurn;
    bool wasDestroyed;
    bool waitingToGetFocus;
    int waitTime;
    size_t idWormCurrentPlay;

 public:
    Worm(const size_t &idWorm, const size_t &idPlayer, const float &posIniX, const float &posIniY,
            const GameParameters &gameParameter, Armament& armament);

    float getHP() const;

    void assigOnABeam();

    void unAssingOnABeam();

    void activaeInclinedBeam();

    void disableInclinedBeam();

    void assigNextToAWorm();

    void unAssignNextToAWorm();

    WormDTO getWormDTO() const;

    void assignBonusLife();

    void addToTheWorld(b2World *world);

    void jump(const TypeJump &typeJump);

    void walk(Direction aDirection);

    WeaponSightDTO getWeaponSightDTO();

    void activateFocus();

    void update();

    void attackWithBat();

    void takeDamage(const float &aDamage);

    void assignWeapon(const TypeWeapon &aTypeWeapon);

    void teleportWorm(const int &posXTeleport, const int &posYTeleport);

    void attack(const CommandDTO &aCommand);

    ProjectilesDTO getProjectilesDTO();

    void savePositionInAir(const float &positionXAir, const float &positionYAir);

    std::pair<float, float> getPositionAir() const;

    void attackWithBazooka();

    void endTurn();

    void execute(const CommandDTO &aCommandDTO, const int &timeLeft, const size_t &idCurrentWorm);

    void tryAttackVariablePower();

    bool wasDamaged() const;

    bool alreadyAttack() const;

    bool isUnmoveAndNotExistsPojectiles();

    bool thereAreProjectiles();

    void walkWorm(const Direction &aDiretion);

    b2World *getWorld();

    bool wasDestroyedWorm() const;

    void chargeWeaponWithVariablePower();

    void changeAngle(const Direction &direction);

    void endAttack();

    void aContactWithEdge();

    void lessContactWithEdge();

    void giveExtraHP(const float &extraHP);

    void giveExtraMunition(const size_t &extraMunition);

    Direction getDirection();

    bool attackWithAirAttack(const int &posXAttack);

    bool attackWithDynamiteHolder();

    void setHP(const float &aNewHP);

    void setWaitTime(const int &aWaitTIme);

    void attackWithGrenade();

    void attackWithMortar();

    bool isStopTheWorm() const;

    void assignTypeFocus(const TypeFocus &focus);

    bool hasTheTeleport() const;

    bool hasTheAirAttack() const;

    TypeFocus getTypeFocus() const;
};


#endif  // WORMS_TALLER_1_WORM_H
