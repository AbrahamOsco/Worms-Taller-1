//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_GAMEOBJECT_H
#define WORMS_TALLER_1_GAMEOBJECT_H

#include "IObject.h"
#include "SDL2pp/SDL2pp.hh"
#include "../loaderParams/LoaderParams.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"

class GameObject : public IObject {
protected:
    int m_x, m_y;
    int m_width, m_height;
    std::string m_textureID;
    SDL_RendererFlip m_flip;

public:
    GameObject();
    explicit GameObject(const LoaderParams &params);
    virtual void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;
    virtual void update(float dt) = 0;
    virtual void processEvent(SDL_Event &event, Queue<std::unique_ptr<Command>>& queue) = 0;
    virtual ~GameObject() {}
};


#endif //WORMS_TALLER_1_GAMEOBJECT_H
