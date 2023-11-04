//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_PLAYER_H


#include "../GameObject.h"
#include "../../loaderParams/LoaderParams.h"
#include "../../animation/Animation.h"

class Worm : public GameObject {
private:
    bool m_isRunning;

    Animation m_animation;

public:
    explicit Worm(const LoaderParams &params);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
};


#endif //WORMS_TALLER_1_WORM_H
