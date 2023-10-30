//
// Created by riclui on 29/10/23.
//

#ifndef WORMS_TALLER_1_BATICON_H
#define WORMS_TALLER_1_BATICON_H


#include "Icon.h"

class BatIcon : public Icon {
public:
    BatIcon();
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
};


#endif //WORMS_TALLER_1_BATICON_H
