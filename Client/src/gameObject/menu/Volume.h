//
// Created by riclui on 28/11/23.
//

#ifndef WORMS_TALLER_1_VOLUME_H
#define WORMS_TALLER_1_VOLUME_H

#include <memory>
#include "../GameObject.h"

class Volume : public GameObject {
 private:
    bool m_activate;

 public:
    Volume();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif  // WORMS_TALLER_1_VOLUME_H
