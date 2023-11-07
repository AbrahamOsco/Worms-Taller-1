//
// Created by riclui on 06/11/23.
//

#ifndef WORMS_TALLER_1_TURN_H
#define WORMS_TALLER_1_TURN_H


#include "../GameObject.h"

class Turn : public GameObject {
private:
    bool m_isTurn;
public:
    Turn(bool isTurn);
    void draw(SDL2pp::Renderer& renderer, TextureManager& textureManager) override {}
    void update(float dt) override {}
    void processEvent(SDL_Event &event, Queue<std::unique_ptr<Command>>& queue) override;
};


#endif //WORMS_TALLER_1_TURN_H
