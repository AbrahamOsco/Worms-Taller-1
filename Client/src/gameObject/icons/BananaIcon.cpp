//
// Created by riclui on 27/10/23.
//

#include "BananaIcon.h"

BananaIcon::BananaIcon() : Icon(LoaderParams(900, 60, 50, 55, "banana_icon")) {}

void BananaIcon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);

    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("../Client/resources/fonts/GROBOLD.ttf", 14);
    SDL2pp::Texture text(renderer, font.RenderText_Blended("Ammo", SDL_Color{0, 0, 0, 255}));
    renderer.Copy(text, SDL2pp::NullOpt, SDL2pp::Rect(900 + m_width, m_y + 10, text.GetWidth(), text.GetHeight()));
    SDL2pp::Texture ammo_count(renderer, font.RenderText_Blended(std::to_string(m_value), SDL_Color{0, 0, 0, 255}));
    renderer.Copy(ammo_count, SDL2pp::NullOpt, SDL2pp::Rect(900 + m_width + 20, m_y + 30, ammo_count.GetWidth(), ammo_count.GetHeight()));
}

void BananaIcon::update(float dt) {}


