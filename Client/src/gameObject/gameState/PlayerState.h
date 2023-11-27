//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_PLAYERSTATE_H
#define WORMS_TALLER_1_PLAYERSTATE_H

#include <memory>
#include "../GameObject.h"
#include "../../soundManager/SoundManager.h"

class PlayerState : public GameObject {
    GameState m_gameState;
    TypeResult m_typeResult;
 public:
    PlayerState(const GameState &gameState, const TypeResult &typeResult);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override {}
};


#endif  // WORMS_TALLER_1_PLAYERSTATE_H
