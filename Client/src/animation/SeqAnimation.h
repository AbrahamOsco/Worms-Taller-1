//
// Created by riclui on 17/11/23.
//

#ifndef WORMS_TALLER_1_SEQANIMATION_H
#define WORMS_TALLER_1_SEQANIMATION_H

#include "SDL2pp/SDL2pp.hh"
#include <string>
#include "Animation.h"
#include "../graphics/TextureManager.h"

class SeqAnimation : public Animation {
private:
    int m_speed;
    int m_frameCount;
    std::string m_textureId;

public:
    explicit SeqAnimation(bool repeat = true);
    void update() override;
    void setRepeat(bool repeat);
    void drawFrame(int x, int y, int width, int height, SDL2pp::Renderer &renderer, TextureManager &textureManager, SDL_RendererFlip flip = SDL_FLIP_NONE, float xScale = 1, float yScale = 1);

    void setProps(const std::string &textureID, int frameCount, int animSpeed);
};


#endif //WORMS_TALLER_1_SEQANIMATION_H
