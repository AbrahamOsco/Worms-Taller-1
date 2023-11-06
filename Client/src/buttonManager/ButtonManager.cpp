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

void ButtonManager::processEvent(SDL_Event &event, Queue<std::unique_ptr<Command>> &queue) {
    for (Button& button : m_buttons) {
        button.processEvent(event, queue);
    }
}

void ButtonManager::arrangeButtonsVerticallyLeftAligned(int verticalSpacing) {
    int totalHeight = getTotalButtonHeight() + (getTotalButtons() - 1) * verticalSpacing;
    int currentY = (WINDOW_HEIGHT - totalHeight) / 2; // Centra verticalmente

    for (Button& button : m_buttons) {
        int x = 0; // Alineación a la izquierda
        button.setX(x);
        button.setY(currentY);
        currentY += button.getHeight() + verticalSpacing;
    }
}

int ButtonManager::getTotalButtonHeight() {
    int totalHeight = 0;
    for (Button& button : m_buttons) {
        totalHeight += button.getHeight();
    }
    return totalHeight;
}

int ButtonManager::getTotalButtons() const {
    return m_buttons.size();
}
