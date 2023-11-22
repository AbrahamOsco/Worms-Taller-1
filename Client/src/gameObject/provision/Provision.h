//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_PROVISION_H
#define WORMS_TALLER_1_PROVISION_H


#include "../GameObject.h"

class Provision : public GameObject{
    TypeEffect m_typeEffect;
    TypeContact m_typeContact;
public:
    Provision(int x, int y, const TypeEffect &typeEffect, const TypeContact &typeContact);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;

};


#endif //WORMS_TALLER_1_PROVISION_H
