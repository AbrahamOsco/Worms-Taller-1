//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include "box2d/box2d.h"
#include "../../../Common/DTO/WormDTO.h"
#include "GameObject.h"

#define LIFE_BONUS 25
enum Direction{
    RIGHT = 1, LEFT = 2
};


class Worm : GameObject {
    size_t idWorm;
    Direction directionLook;
    float  hp;
    float dragSpeed;
    float positionInitialX;
    float positionInitialY;
    std::pair<float, float> jumpForward;
    std::pair<float, float> jumpBack;
    size_t numberContacts;

public:
    Worm(const size_t &idWorm, const float &posIniX, const float &posIniY);

    void assignBonusLife();

    WormDTO getWormInitialDTO() const;

    void addToTheWorld(b2World *world);

    void jumpBackwards();

    void jumpForwards();

    void walk(Direction aDirection);

    //void startContact();

    //void endContact();

    //void render();
};


#endif //WORMS_TALLER_1_WORM_H
