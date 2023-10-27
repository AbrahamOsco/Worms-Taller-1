//
// Created by riclui on 27/10/23.
//

#ifndef WORMS_TALLER_1_BANANAICON_H
#define WORMS_TALLER_1_BANANAICON_H


#include "Icon.h"

class BananaIcon : public Icon {
public:
    BananaIcon();
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override;
    void update(float dt) override;
};


#endif //WORMS_TALLER_1_BANANAICON_H
