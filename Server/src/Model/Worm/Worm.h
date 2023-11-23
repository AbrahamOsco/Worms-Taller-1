//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

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
    TypeFocus typeFocus; // 1 Si esta siendo focus , 2 sino.
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
    std::pair<float, float> positionInAir; // para que el gusano sufra daño en caidas mayores a 2m.
    TypeCharge typeCharge;
    float hpInitialTurn;
    bool wasDestroyed;
    bool waitingToGetFocus;
    int waitTime;
public:

    Worm(const size_t &idWorm, const size_t &idPlayer, const float &posIniX, const float &posIniY, const GameParameters &gameParameter,
         Armament& armament);

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

    bool isInContactWithAnotherWorm();

    WeaponSightDTO getWeaponSightDTO();

    void activateFocus();

    void update();

    void attackWithBat();

    void takeDamage(const float &aDamage);

    void assignWeapon(const TypeWeapon &aTypeWeapon);

    void teleportWorm(const int &posXTeleport, const int &posYTeleport);

    void attack(std::unique_ptr<CommandDTO> &aCommand);

    ProjectilesDTO getProjectilesDTO();

    void savePositionInAir(const float &positionXAir, const float &positionYAir);

    std::pair<float, float> getPositionAir() const;

    void attackWithBazooka();

    void endTurn();

    void execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft, size_t idCurrentWorm);

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
};


#endif //WORMS_TALLER_1_WORM_H
