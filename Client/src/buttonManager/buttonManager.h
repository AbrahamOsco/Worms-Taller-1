//
// Created by riclui on 29/10/23.
//

#ifndef WORMS_TALLER_1_BUTTONMANAGER_H
#define WORMS_TALLER_1_BUTTONMANAGER_H


#include "../utils/Constants.h"
#include "../gameObject/button/Button.h"

class buttonManager {
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
public:
    void addButton(std::unique_ptr<Button>);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager);

    void arrangeButtonsVerticallyLeftAligned(int verticalSpacing) {
        int totalHeight = getTotalButtonHeight() + (getTotalButtons() - 1) * verticalSpacing;
        int currentY = (WINDOW_HEIGHT - totalHeight) / 2; // Centra verticalmente

        for (auto& button : m_buttons) {
            int x = 0; // Alineación a la izquierda
            button->setX(x);
            button->setY(currentY);
            currentY += button->getHeight() + verticalSpacing;
        }
    }

    int getTotalButtonHeight() const {
        int totalHeight = 0;
        for (const auto& button : m_buttons) {
            totalHeight += button->getHeight();
        }
        return totalHeight;
    }

    int getTotalButtons() const {
        return m_buttons.size();
    }
};


#endif //WORMS_TALLER_1_BUTTONMANAGER_H
