//
// Created by riclui on 25/10/23.
//

#include "LoaderParams.h"

LoaderParams::LoaderParams(float x, float y, int width, int height, std::string &textureID, SDL_RendererFlip flip)
: m_x(x), m_y(y), m_width(width), m_height(height), m_flip(flip),m_textureID(textureID) {}

float LoaderParams::getX() const { return m_x; }

float LoaderParams::getY() const { return m_y; }

int LoaderParams::getWidth() const { return m_width; }

int LoaderParams::getHeight() const { return m_height; }

const std::string &LoaderParams::getTextureID() const { return m_textureID; }

SDL_RendererFlip LoaderParams::getFlip() const { return m_flip; }
