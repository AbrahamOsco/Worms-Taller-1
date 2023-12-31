//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_SPRITEANIMATION_H
#define WORMS_TALLER_1_SPRITEANIMATION_H

#include <string>
#include "SDL2pp/SDL2pp.hh"
#include "../graphics/TextureManager.h"
#include "Animation.h"


class SpriteAnimation : public Animation {
 private:
    int m_speed;
    int m_frameCount;
    std::string m_textureId;

 public:
    explicit SpriteAnimation(bool repeat = true);

    void update() override;

    void
    draw(int x, int y, int width, int height, SDL2pp::Renderer &renderer, TextureManager &textureManager,
         SDL_RendererFlip flip = SDL_FLIP_NONE, float xScale = 1, float yScale = 1);

    void setProps(const std::string &textureID, int frameCount, int animSpeed);
};


#endif  // WORMS_TALLER_1_SPRITEANIMATION_H
