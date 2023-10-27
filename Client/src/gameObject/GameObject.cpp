//
// Created by riclui on 25/10/23.
//

#include "GameObject.h"

GameObject::GameObject(const LoaderParams &params) : m_x(params.getX()), m_y(params.getY()), m_width(params.getWidth()), m_height(params.getHeight()),m_textureID(params.getTextureID()), m_flip(params.getFlip()) {}