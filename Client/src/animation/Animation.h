//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_ANIMATION_H
#define WORMS_TALLER_1_ANIMATION_H

#include "SDL2pp/SDL2pp.hh"
#include "../graphics/TextureManager.h"
#include <string>

class Animation {
private:
    int m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;

public:
    Animation() {}
    void update();
    void draw(int x, int y, int spritWidth, int spriteHeight, SDL2pp::Renderer &renderer, TextureManager &textureManager);
    void setProps(std::string &textureID, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


#endif //WORMS_TALLER_1_ANIMATION_H
