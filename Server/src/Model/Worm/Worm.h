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

#define LIFE_BONUS 25
enum TypeJump{
    JUMP_BACKWARDS, JUMP_FORWARDS
};
enum TypeCharge{
    NONE_CHARGE, FIRST_CHARGE, MANY_CHARGE
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
    TypeFocusWorm typeFocus; // 1 Si esta siendo focus , 2 sino.
    MoveWorm typeMov;
    const GameParameters& gameParameters;
    b2World* aWorld;
    Armament& armament;
    bool onInclinedBeam;
    bool attacked;
    size_t iterationsForBatAttack;
    std::pair<float, float> positionInAir; // para que el gusano sufra daño en caidas mayores a 2m.
    TypeCharge typeCharge;
public:

    Worm(const size_t &idWorm, const size_t &idPlayer, const float &posIniX, const float &posIniY, const GameParameters &gameParameter,
         Armament& armament);

    float getHP() const;

    // Posibles getters que si no se usan se eliminaran en un futuro todo
    Direction getDirectionLook() const;

    float getPositionX() const;

    float getPositionY();

    void activaeInclinedBeam();

    void disableInclinedBeam();

    TypeFocusWorm getTypeFocusWorm() const;

    MoveWorm getTypeMov() const;

    TypeWeapon getWeaponCurrent() const;

    WormDTO getWormDTO() const;

    void assignBonusLife();

    void addToTheWorld(b2World *world);

    void jump(const TypeJump &typeJump);

    void walk(Direction aDirection);

    bool isInContactWithAnotherWorm();

    WeaponSightDTO getWeaponSightDTO();

    //void startContact();

    //void endContact();

    //void render();

    void activateFocus();

    void leftWorm();

    void rightWorm();

    void update();

    void attackWithBat();

    void takeDamage(const float &aDamage);

    void assignWeapon(const TypeWeapon &aTypeWeapon);

    void teleportWorm(const float &posXTeleport, const float &posYTeleport);

    void upWorm();

    void downWorm();

    void increaseImpulse();

    void attack();

    ProjectilesDTO getProjectilesDTO();

    void savePositionInAir(const float &positionXAir, const float &positionYAir);

    std::pair<float, float> getPositionAir() const;

    void attackWithBazooka();

    void endTurn();

    void execute(std::unique_ptr<CommandDTO> &aCommandDTO);

    void tryAttack();
};


#endif //WORMS_TALLER_1_WORM_H
