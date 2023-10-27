//
// Created by riclui on 27/10/23.
//

#ifndef WORMS_TALLER_1_AIRATTACKICON_H
#define WORMS_TALLER_1_AIRATTACKICON_H


#include "Icon.h"

class AirAttackIcon : public Icon {
public:
    AirAttackIcon();
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;

};


#endif //WORMS_TALLER_1_AIRATTACKICON_H
