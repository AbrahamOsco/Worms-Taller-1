//
// Created by riclui on 29/10/23.
//

#include "buttonManager.h"

void buttonManager::addButton(std::unique_ptr<Button> button) {
    m_buttons.push_back(std::move(button));
}

void buttonManager::draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) {
    arrangeButtonsVerticallyLeftAligned(20);
    for (const auto& button : m_buttons) {
        button->draw(renderer, textureManager);
    }
}
