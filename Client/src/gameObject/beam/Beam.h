//
// Created by riclui on 30/10/23.
//

#ifndef WORMS_TALLER_1_BEAM_H
#define WORMS_TALLER_1_BEAM_H

#include "../GameObject.h"

enum Angle {
    ANGLE_0 = 0,
    ANGLE_10 = 10,
    ANGLE_20 = 20,
    ANGLE_30 = 30,
    ANGLE_40 = 40,
    ANGLE_50 = 50,
    ANGLE_60 = 60,
    ANGLE_70 = 70,
    ANGLE_80 = 80,
    ANGLE_90 = 90,
    ANGLE_100 = 100,
    ANGLE_110 = 110,
    ANGLE_120 = 120,
    ANGLE_130 = 130,
    ANGLE_140 = 140,
    ANGLE_150 = 150,
    ANGLE_160 = 160,
    ANGLE_170 = 170
};

enum BeamType {
    SHORT_BEAM = 3,
    LONG_BEAM = 6
};

class Beam : public GameObject{
private:
    BeamType m_type;
    Angle m_angle;
public:
    Beam(int posCenterX, int posCenterY, Angle angle, BeamType type);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
};


#endif //WORMS_TALLER_1_BEAM_H
