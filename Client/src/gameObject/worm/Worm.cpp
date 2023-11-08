//
// Created by riclui on 25/10/23.
//

#include "Worm.h"

Worm::Worm(const LoaderParams &params, const size_t& hpWorm, const Direction& direction, const TypeFocusWorm& focus, const MoveWorm& moveWorm) : GameObject(params), m_hpWorm(hpWorm), m_directionLook(direction), m_typeFocus(focus), m_moveWorm(moveWorm) {
    m_flip = SDL_FLIP_NONE;
    m_animation.setProps(m_textureID, m_width, m_height, 14, 80);
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL_Rect rect = {m_x - 20, m_y - 30, 36, 15}; // Coordenadas (x, y) y tamaño (ancho, alto) del cuadrado
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255); // Color negro: (R, G, B, Alpha)
    SDL_RenderFillRect(renderer.Get(), &rect); // Dibujar el cuadrado

    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("../Client/resources/fonts/GROBOLD.ttf", 11);
    SDL2pp::Texture text(renderer, font.RenderText_Blended(std::to_string(m_hpWorm), SDL_Color{225, 225, 225, 255}));

// Obtener las dimensiones del texto
    int textWidth = text.GetWidth();
    int textHeight = text.GetHeight();

// Calcular la posición para centrar el texto horizontalmente dentro del rectángulo
    int textX = rect.x + (rect.w - textWidth) / 2; // Centrar en el eje x
    int textY = rect.y + (rect.h - textHeight) / 2; // Centrar en el eje y

    renderer.Copy(text, SDL2pp::NullOpt, SDL2pp::Rect(textX, textY, textWidth, textHeight));


    m_animation.draw(m_x - m_width/2, m_y - m_height/2, m_flip,renderer, textureManager);
}

void Worm::update(float dt) {
    if ( m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    m_animation.update();
    animationState();
}

void Worm::animationState() {
    m_animation.setProps("player", m_width, m_height, 14, 80, SDL_FLIP_NONE);

    if (m_moveWorm == MoveWorm::WALKING) {
        m_width = 30;
        m_height = 30;
        m_animation.setProps("walk", 30, 30,14, 80, SDL_FLIP_NONE);
    }
}
