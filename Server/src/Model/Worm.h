//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include "box2d/box2d.h"
#include "GameObject.h"

#define LIFE_BONUS 25
enum Direction{
    RIGHT = 1, LEFT = 2
};
enum TypeFocusWorm{
    FOCUS = 1, NO_FOCUS = 2
};
enum MoveWorm{
    STANDING = 1, WALKING = 2, JUMPING =3
};

class Worm : public GameObject {
    size_t idWorm;
    Direction directionLook;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;
    std::pair<float, float> jumpForward;
    std::pair<float, float> jumpBack;
    size_t numberContacts;
    TypeFocusWorm typeFocus; // 1 Si esta siendo focus , 2 sino.
    MoveWorm typeMov;
public:

    Worm();

    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY);

    Direction getDirectionLook() const;

    float getPositionX() const;

    float getPositionY();

    float getHP() const;

    TypeFocusWorm getTypeFocusWorm() const;

    MoveWorm getTypeMov() const;

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
};


#endif //WORMS_TALLER_1_WORM_H
