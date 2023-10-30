//
// Created by riclui on 27/10/23.
//

#include "Button.h"

Button::Button(const std::string &textureID) : GameObject(LoaderParams(0, 0, 50, 55, textureID)) {
    m_value = 0;
}

void Button::setX(int x) {
    m_x = x;
}

void Button::setY(int y) {
    m_y = y;
}

int Button::getHeight() {
    return m_height;
}

void Button::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);

    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("../Client/resources/fonts/GROBOLD.ttf", 14);
    SDL2pp::Texture text(renderer, font.RenderText_Blended("Ammo", SDL_Color{0, 0, 0, 255}));
    renderer.Copy(text, SDL2pp::NullOpt, SDL2pp::Rect(m_width, m_y + 10, text.GetWidth(), text.GetHeight()));
    SDL2pp::Texture ammo_count(renderer, font.RenderText_Blended(std::to_string(m_value), SDL_Color{0, 0, 0, 255}));
    renderer.Copy(ammo_count, SDL2pp::NullOpt, SDL2pp::Rect(m_width + 20, m_y + 30, ammo_count.GetWidth(), ammo_count.GetHeight()));
}

void Button::update(float dt) {}
