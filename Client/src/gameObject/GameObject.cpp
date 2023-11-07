//
// Created by riclui on 25/10/23.
//

#include "GameObject.h"

GameObject::GameObject(const LoaderParams &params) : m_x(params.getX()), m_y(params.getY()), m_width(params.getWidth()), m_height(params.getHeight()),m_textureID(params.getTextureID()), m_flip(params.getFlip()) {}

GameObject::GameObject() : m_x(0), m_y(0), m_width(0), m_height(0), m_textureID(" "), m_flip(SDL_FLIP_NONE) {}
