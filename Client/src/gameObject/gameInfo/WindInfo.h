//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WINDINFO_H
#define WORMS_TALLER_1_WINDINFO_H

#include <memory>
#include "../../../../Common/DTO/WormDTO.h"
#include "../GameObject.h"

class WindInfo : public GameObject {
 private:
    int m_velocity;
    TypeWind m_direction;
 public:
    WindInfo(int velocity, TypeWind direction);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override {}
};


#endif  // WORMS_TALLER_1_WINDINFO_H
