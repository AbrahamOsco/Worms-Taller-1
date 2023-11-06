//
// Created by riclui on 29/10/23.
//

#ifndef WORMS_TALLER_1_BUTTONMANAGER_H
#define WORMS_TALLER_1_BUTTONMANAGER_H


#include "../utils/Constants.h"
#include "../gameObject/button/Button.h"

class ButtonManager : public GameObject {
private:
    std::vector<Button> m_buttons;
public:
    ButtonManager(const LoaderParams &params, std::vector<Button>&& buttons);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
    void processEvent(SDL_Event &event, Queue<std::unique_ptr<Command>>& queue) override;
    void arrangeButtonsVerticallyLeftAligned(int verticalSpacing);
    int getTotalButtonHeight();
    int getTotalButtons() const;
};


#endif //WORMS_TALLER_1_BUTTONMANAGER_H
