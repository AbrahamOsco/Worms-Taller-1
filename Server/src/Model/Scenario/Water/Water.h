//
// Created by abraham on 03/11/23.
//

#ifndef WORMS_TALLER_1_WATER_H
#define WORMS_TALLER_1_WATER_H


#include "../../GameObject/GameObject.h"

class Water : public GameObject{
private:

public:
    Water();

    Water(b2World* world, const float& height, const float& width);

};


#endif //WORMS_TALLER_1_WATER_H
