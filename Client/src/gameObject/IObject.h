//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_IOBJECT_H
#define WORMS_TALLER_1_IOBJECT_H

#include <memory>
#include "SDL2pp/SDL2pp.hh"
#include "../graphics/TextureManager.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"
#include "../inputs/Input.h"
#include "../camera/Camera.h"
#include "../soundManager/SoundManager.h"

class IObject {
 public:
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) = 0;

    virtual void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) = 0;

    virtual ~IObject() = default;
};

#endif  // WORMS_TALLER_1_IOBJECT_H
