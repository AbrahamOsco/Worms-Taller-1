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
#include "../gameObject/beam/Beam.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"
#include "../inputs/Input.h"

class Engine {
private:
    TextureManager m_textureManager;
    bool m_running;
    SDL2pp::Window m_window;
    SDL2pp::Renderer m_renderer;
    Input m_input;
    Timer m_timer;

    std::vector<Beam> &m_beams;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;

    Queue<std::unique_ptr<Command>> &m_bQueue;
    Queue<std::vector<std::unique_ptr<GameObject>>> &m_nbQueue;

public:
    Engine(std::vector<Beam> &beams, Queue<std::unique_ptr<Command>> &bQueue,
           Queue<std::vector<std::unique_ptr<GameObject>>> &nbQueue);

    ~Engine() = default;

    void init();

    void events();

    void update();

    void render();

    bool running() const;

    void tick();
};


#endif //WORMS_TALLER_1_ENGINE_H
