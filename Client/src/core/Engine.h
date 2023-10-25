//
// Created by riclui on 24/10/23.
//

#ifndef WORMS_TALLER_1_ENGINE_H
#define WORMS_TALLER_1_ENGINE_H


#include <memory>
#include "../graphics/TextureManager.h"
#include "../timer/Timer.h"
#include "../gameObject/GameObject.h"
#include "../loaderParams/LoaderParams.h"

class Engine {
private:
    TextureManager m_textureManager;
    bool m_bRunning;
    SDL2pp::Window m_pWindow;
    SDL2pp::Renderer m_pRenderer;
    Timer m_timer;

    std::vector<std::unique_ptr<GameObject>> m_gameObjects;

public:
    Engine();
    ~Engine() = default;
    void init();
    void render();
    void update();
    void events();
    bool running() const;
    void tick();
};


#endif //WORMS_TALLER_1_ENGINE_H
