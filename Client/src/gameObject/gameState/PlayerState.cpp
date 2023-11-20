//
// Created by riclui on 20/11/23.
//

#include "PlayerState.h"

PlayerState::PlayerState(const GameState &gameState, const TypeResult &typeResult) : m_gameState(gameState), m_typeResult(typeResult) {}

void PlayerState::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    if (m_gameState == GameState::GAME_END) {
        if (m_typeResult == TypeResult::WON_THE_GAME) {
            textureManager.draw("victory", 0, 0, 1876, 1208, renderer);
        } else {
            textureManager.draw("defeat", 0, 0, 1800, 1142, renderer);
        }
    }
}
