//
// Created by riclui on 30/10/23.
//

#include "Beam.h"

Beam::Beam(int posCenterX, int posCenterY, Angle angle, BeamType type) : GameObject(LoaderParams(0, 0, 0, 0, "")) {
    m_type = type;
    m_angle = angle;
    m_textureID = "beam_" + std::to_string(m_type) + "_" + std::to_string(m_angle);
    std::cout << m_textureID << std::endl;
    if (type == SHORT_BEAM) {
        if (angle == ANGLE_0) {
            m_width = 180;
            m_height = 24;
        } else if (angle == ANGLE_10 || angle == ANGLE_170) {
            m_width = 181;
            m_height = 54;
        } else if (angle == ANGLE_20 || angle == ANGLE_160) {
            m_width = 177;
            m_height = 84;
        } else if (angle == ANGLE_30 || angle == ANGLE_150) {
            m_width = 167;
            m_height = 110;
        } else if (angle == ANGLE_40 || angle == ANGLE_140) {
            m_width = 153;
            m_height = 134;
        } else if (angle == ANGLE_50 || angle == ANGLE_130) {
            m_width = 134;
            m_height = 153;
        } else if (angle == ANGLE_60 || angle == ANGLE_120) {
            m_width = 110;
            m_height = 167;
        } else if (angle == ANGLE_70 || angle == ANGLE_110) {
            m_width = 84;
            m_height = 177;
        } else if (angle == ANGLE_80 || angle == ANGLE_100) {
            m_width = 54;
            m_height = 181;
        } else if (angle == ANGLE_90) {
            m_width = 23;
            m_height = 180;
        }
    } else if (type == LONG_BEAM) {
        if (angle == ANGLE_0) {
            m_width = 360;
            m_height = 24;
        } else if (angle == ANGLE_10 || angle == ANGLE_170) {
            m_width = 358;
            m_height = 86;
        } else if (angle == ANGLE_20 || angle == ANGLE_160) {
            m_width = 346;
            m_height = 145;
        } else if (angle == ANGLE_30 || angle == ANGLE_150) {
            m_width = 323;
            m_height = 200;
        } else if (angle == ANGLE_40 || angle == ANGLE_140) {
            m_width = 291;
            m_height = 249;
        } else if (angle == ANGLE_50 || angle == ANGLE_130) {
            m_width = 249;
            m_height = 291;
        } else if (angle == ANGLE_60 || angle == ANGLE_120) {
            m_width = 200;
            m_height = 323;
        } else if (angle == ANGLE_70 || angle == ANGLE_110) {
            m_width = 145;
            m_height = 346;
        } else if (angle == ANGLE_80 || angle == ANGLE_100) {
            m_width = 86;
            m_height = 358;
        } else if (angle == ANGLE_90) {
            m_width = 24;
            m_height = 360;
        }
    }

    m_x = posCenterX - m_width/2;
    m_y = posCenterY - m_height/2;
    std::cout << "(" << m_x << "," << m_y <<")" << std::endl;
}

void Beam::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);
}

void Beam::update(float dt) {
}