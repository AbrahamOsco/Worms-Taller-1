//
// Created by riclui on 25/10/23.
//

#include "LoaderParams.h"

LoaderParams::LoaderParams() : m_x(0), m_y(0), m_width(0), m_height(0), m_flip(SDL_FLIP_NONE), m_textureID(" ") {}

LoaderParams::LoaderParams(int x, int y, int width, int height, const std::string &textureID, SDL_RendererFlip flip)
: m_x(x), m_y(y), m_width(width), m_height(height), m_flip(flip), m_textureID(textureID) {}

int LoaderParams::getX() const { return m_x; }

int LoaderParams::getY() const { return m_y; }

int LoaderParams::getWidth() const { return m_width; }

int LoaderParams::getHeight() const { return m_height; }

const std::string &LoaderParams::getTextureID() const { return m_textureID; }

SDL_RendererFlip LoaderParams::getFlip() const { return m_flip; }


