//
// Created by riclui on 27/10/23.
//

#ifndef WORMS_TALLER_1_BUTTON_H
#define WORMS_TALLER_1_BUTTON_H


#include "../GameObject.h"

class Button : public GameObject{
protected:
    int m_value;
public:
    explicit Button(const std::string &textureID);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager);
    void update(float dt);
    void setX(int x);
    void setY(int y);
    int getHeight();

};


#endif //WORMS_TALLER_1_BUTTON_H
