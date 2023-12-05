//
// Created by abraham on 03/11/23.
//

#ifndef WORMS_TALLER_1_EDGES_H
#define WORMS_TALLER_1_EDGES_H


#include "../../GameObject/GameObject.h"

class Edges : public  GameObject {
 public:
    Edges();

    Edges(b2World* world, const float& height, const float& width);
};


#endif  // WORMS_TALLER_1_EDGES_H
