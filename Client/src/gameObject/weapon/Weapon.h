//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPON_H
#define WORMS_TALLER_1_WEAPON_H


#include "../GameObject.h"

class Weapon : public GameObject {
private:
    int m_ammoCount;
public:
    Weapon(const std::string &weapon, int ammoCount);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override {}

    void setParams(int x, int y);

    int getHeight();
};


#endif //WORMS_TALLER_1_WEAPON_H
