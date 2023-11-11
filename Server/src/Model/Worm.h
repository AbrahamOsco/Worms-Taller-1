//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include "box2d/box2d.h"
#include "GameObject.h"
#include "../../../Common/DTO/WormDTO.h"
#include "../../GameParameters/GameParameters.h"
#include "Armament.h"

#define LIFE_BONUS 25

class Worm : public GameObject {
    size_t idWorm;
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
public:

    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY, const GameParameters &gameParameter,
         Armament& armament);

    float getHP() const;

    // Posibles getters que si no se usan se eliminaran en un futuro todo
    Direction getDirectionLook() const;

    float getPositionX() const;

    float getPositionY();

    TypeFocusWorm getTypeFocusWorm() const;

    MoveWorm getTypeMov() const;

    TypeWeapon getWeaponCurrent() const;

    WormDTO getWormDTO() const;

    void assignBonusLife();

    void addToTheWorld(b2World *world);

    void jumpBackwards();

    void jumpForwards();

    void walk(Direction aDirection);

    bool isInContactWithAnotherWorm();

    //void startContact();

    //void endContact();

    //void render();

    void activateFocus();

    void leftWorm();

    void rightWorm();

    void stopIfUnmoving();

    void attackWithBat();

    void takeDamage(const float &aDamage);

    void assignWeapon(const TypeWeapon &aTypeWeapon);


};


#endif //WORMS_TALLER_1_WORM_H
