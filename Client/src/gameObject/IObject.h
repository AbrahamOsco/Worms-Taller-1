//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_IOBJECT_H
#define WORMS_TALLER_1_IOBJECT_H

#include "SDL2pp/SDL2pp.hh"
#include "../graphics/TextureManager.h"

class IObject {
public:
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
    virtual void update(float dt) = 0;

    virtual ~IObject() {}

};

#endif //WORMS_TALLER_1_IOBJECT_H