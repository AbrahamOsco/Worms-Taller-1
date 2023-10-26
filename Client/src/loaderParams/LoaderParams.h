//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_LOADERPARAMS_H
#define WORMS_TALLER_1_LOADERPARAMS_H

#include "SDL2pp/SDL2pp.hh"
#include <string>

class LoaderParams {
private:
    float m_x;
    float m_y;
    int m_width;
    int m_height;
    std::string m_textureID;
    SDL_RendererFlip m_flip;

public:
    LoaderParams(float x, float y, int width, int height, const std::string &textureID, SDL_RendererFlip flip = SDL_FLIP_NONE);

    float getX() const;

    float getY() const;

    int getWidth() const;

    int getHeight() const;

    const std::string &getTextureID() const;

    SDL_RendererFlip getFlip() const;
};


#endif //WORMS_TALLER_1_LOADERPARAMS_H