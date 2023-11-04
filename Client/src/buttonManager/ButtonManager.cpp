//
// Created by riclui on 29/10/23.
//

#include "ButtonManager.h"

ButtonManager::ButtonManager(const LoaderParams &params, std::vector<Button>&& buttons) : GameObject(params),  m_buttons(std::move(buttons)) {}

void ButtonManager::draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) {
    arrangeButtonsVerticallyLeftAligned(20);
    for (Button& button : m_buttons) {
        button.draw(renderer, textureManager);
    }
}

void ButtonManager::update(float dt) {}
