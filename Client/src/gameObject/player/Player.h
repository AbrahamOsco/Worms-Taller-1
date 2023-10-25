//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H


#include "../GameObject.h"
#include "../../loaderParams/LoaderParams.h"
#include "../../animation/Animation.h"

class Player : public GameObject {
private:
    Animation m_animation;

public:
    explicit Player(const LoaderParams &params);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
};


#endif //WORMS_TALLER_1_PLAYER_H
