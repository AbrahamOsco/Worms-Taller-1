//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_GAMEOBJECT_H
#define WORMS_TALLER_1_GAMEOBJECT_H

#include "IObject.h"
#include "SDL2pp/SDL2pp.hh"
#include "../loaderParams/LoaderParams.h"

class GameObject : public IObject {
protected:
    //Transform m_transform;
    int m_width, m_height;
    std::string m_textureID;
    SDL_RendererFlip m_flip;

public:
    explicit GameObject(const LoaderParams &params);

    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

    virtual void update(float dt) = 0;

    virtual ~GameObject() {}
};


#endif //WORMS_TALLER_1_GAMEOBJECT_H
