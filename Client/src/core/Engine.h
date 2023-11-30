//
// Created by riclui on 24/10/23.
//

#ifndef WORMS_TALLER_1_ENGINE_H
#define WORMS_TALLER_1_ENGINE_H

#include <string>
#include <vector>
#include <memory>
#include "../graphics/TextureManager.h"
#include "../timer/Timer.h"
#include "../gameObject/GameObject.h"
#include "../loaderParams/LoaderParams.h"
#include "../gameObject/beam/Beam.h"
#include "../command/Command.h"
#include "../../../Common/Queue/Queue.h"
#include "../inputs/Input.h"
#include "../soundManager/SoundManager.h"
#include "../gameObject/water/Water.h"
#include "../gameObject/menu/Volume.h"

class Engine {
 private:
    TextureManager m_textureManager;
    SoundManager m_soundManager;
    std::atomic<bool>& m_running;
    SDL2pp::Window m_window;
    SDL2pp::Renderer m_renderer;
    Input m_input;
    Timer m_timer;

    std::vector<Beam> &m_beams;

    Volume m_volume;
    std::string m_background;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;

    Camera m_camera;

    Queue<std::unique_ptr<Command>> &m_bQueue;
    Queue<std::vector<std::unique_ptr<GameObject>>> &m_nbQueue;

 public:
    Engine(std::vector<Beam> &beams, const std::string &background,
            Queue<std::unique_ptr<Command>> &bQueue,
            Queue<std::vector<std::unique_ptr<GameObject>>> &nbQueue, std::atomic<bool>& running);

    ~Engine() = default;

    void init();

    void events();

    void update();

    void render();

    bool running() const;

    void tick();
};


#endif  // WORMS_TALLER_1_ENGINE_H
