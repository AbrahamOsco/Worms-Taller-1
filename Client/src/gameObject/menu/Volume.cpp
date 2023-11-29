//
// Created by riclui on 28/11/23.
//

#include "Volume.h"
#include "../../utils/Constants.h"

Volume::Volume() : GameObject(LoaderParams(0, 0, 40, 36, "volume")), m_activate(true) {
    int padding = 5;
    m_x = WINDOW_WIDTH - m_width - padding;
    m_y = padding;
}

void Volume::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    SDL2pp::Rect shape = SDL2pp::Rect(m_x, m_y, m_width, m_height);
    SDL2pp::Point point(input.getMouseX(), input.getMouseY());
    if (input.isMouseLeftButtonDown() && SDL_PointInRect(&point, &shape) && m_activate && !input.getPress()) {
        input.setPress(true);
        m_activate = false;
        soundManager.stopMusic();

    } else if (input.isMouseLeftButtonDown() && SDL_PointInRect(&point, &shape) && !m_activate && !input.getPress()) {
        input.setPress(true);
        m_activate = true;
        soundManager.playMusic("background_music");
    }

    if (!input.isMouseLeftButtonDown()) {
        input.setPress(false);
    }
}

void Volume::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    if (m_activate) {
        textureManager.draw("volume_on", m_x, m_y, m_width, m_height, renderer);
    } else {
        textureManager.draw("volume_off", m_x, m_y, m_width, m_height, renderer);
    }
}


