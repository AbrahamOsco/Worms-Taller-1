//
// Created by riclui on 27/10/23.
//

#ifndef WORMS_TALLER_1_ICON_H
#define WORMS_TALLER_1_ICON_H


#include "../GameObject.h"

class Icon : public GameObject{
protected:
    int m_value;
public:
    explicit Icon(const LoaderParams &params);
    virtual void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) = 0;
    virtual void update(float dt) = 0;
};


#endif //WORMS_TALLER_1_ICON_H
