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
#include "../buttonManager/buttonManager.h"
#include "../gameObject/beam/Beam.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"

class Engine {
private:
    TextureManager m_textureManager;
    bool m_bRunning;
    SDL2pp::Window m_pWindow;
    SDL2pp::Renderer m_pRenderer;
    Timer m_timer;

    std::vector<std::unique_ptr<Beam>>& m_beams;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    buttonManager m_buttons;

    Queue<std::unique_ptr<Command>>& m_bQueue;

public:
    Engine(std::vector<std::unique_ptr<Beam>>& beams, Queue<std::unique_ptr<Command>>& bQueue);
    ~Engine() = default;
    void init();
    void events();
    void update();
    void render();
    bool running() const;
    void tick();
};


#endif //WORMS_TALLER_1_ENGINE_H
