//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_IOBJECT_H
#define WORMS_TALLER_1_IOBJECT_H

#include "SDL2pp/SDL2pp.hh"
#include "../graphics/TextureManager.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"
#include "../inputs/Input.h"

class IObject {
public:
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

    virtual void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) = 0;

    virtual ~IObject() = default;

};

#endif //WORMS_TALLER_1_IOBJECT_H
