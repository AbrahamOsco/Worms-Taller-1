//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H


#include "../GameObject.h"
#include "../../loaderParams/LoaderParams.h"
#include "../../animation/SpriteAnimation.h"
#include <cmath>

class Worm : public GameObject {
protected:
    size_t m_hpWorm;
    Direction m_directionLook;
    MoveWorm m_moveWorm;
    TypeFocusWorm m_typeFocus;
    SpriteAnimation m_animation;

public:
    explicit Worm(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus, const MoveWorm &moveWorm);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) override;

    void animationState();

};


#endif //WORMS_TALLER_1_WORM_H
