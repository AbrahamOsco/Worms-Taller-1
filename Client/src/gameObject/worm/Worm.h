//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H

#include <cmath>
#include <memory>
#include "../GameObject.h"
#include "../../loaderParams/LoaderParams.h"
#include "../../animation/SpriteAnimation.h"
#include "../../soundManager/SoundManager.h"


class Worm : public GameObject {
 protected:
    int m_id;
    size_t m_hpWorm;
    Direction m_directionLook;
    MoveWorm m_moveWorm;
    TypeFocus m_typeFocus;
    SpriteAnimation m_animation;
    bool m_isMyTurn;

 public:
    explicit Worm(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                const TypeFocus &focus, const MoveWorm &moveWorm, bool isMyTurn);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;

    void animationState();
};


#endif  // WORMS_TALLER_1_WORM_H
