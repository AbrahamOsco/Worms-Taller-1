//
// Created by abraham on 19/11/23.
//

#ifndef WORMS_TALLER_1_PROVISION_H
#define WORMS_TALLER_1_PROVISION_H


#include <utility>
#include "box2d/box2d.h"
#include <box2d/b2_world.h>
#include "../../../../Common/DTO/ProvisionDTO.h"
#include "../../../GameParameters/GameParameters.h"
#include "../GameObject/GameObject.h"
#include "../Worm/Worm.h"

class Provision : public GameObject {
private:
    std::pair<float, float> position;
    TypeEffect typeEffect;
    GameParameters gameParameters;
    b2World* world;
    int animationIterations;

public:
    Provision(const float &positionX, const float &positionY, const TypeEffect &typeEffect, const GameParameters& parameters);

    void addToTheWorld(b2World *world);

    void getProvisionDTO(std::vector<ProvisionDTO> &vecProvisionDTO);

    void applyEffect(Worm *wormSelect);

    bool hasIterations() const;
};


#endif //WORMS_TALLER_1_PROVISION_H
