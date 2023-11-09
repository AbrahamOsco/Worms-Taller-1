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
    size_t m_hpWorm;
    Direction m_directionLook;
    MoveWorm m_moveWorm;
    TypeFocusWorm m_typeFocus;

    Animation m_animation;

public:
    explicit Worm(const LoaderParams &params, const size_t &hpWorm, const Direction &direction,
                  const TypeFocusWorm &focus, const MoveWorm &moveWorm);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override;

    void animationState();
};


#endif //WORMS_TALLER_1_WORM_H
