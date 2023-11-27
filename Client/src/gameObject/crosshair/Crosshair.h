//
// Created by riclui on 13/11/23.
//

#ifndef WORMS_TALLER_1_CROSSHAIR_H
#define WORMS_TALLER_1_CROSSHAIR_H

#include <memory>
#include "../GameObject.h"
#include "../../animation/SpriteAnimation.h"
#include "../../soundManager/SoundManager.h"

class Crosshair : public GameObject {
    TypeSight m_typeSight;
    SpriteAnimation m_animation;

 public:
    Crosshair(int x, int y, const TypeSight &typeSight);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue,
            Camera &camera, SoundManager &soundManager) override;
};


#endif  // WORMS_TALLER_1_CROSSHAIR_H
