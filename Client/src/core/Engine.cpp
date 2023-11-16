//
// Created by riclui on 24/10/23.
//

#include "Engine.h"
#include "../gameObject/worm/Worm.h"
#include "../utils/Constants.h"
#include "../gameObject/beam/Beam.h"
#include "../command/RightCmd.h"
#include "../command/LeftCmd.h"

Engine::Engine(std::vector<Beam> &beams, Queue<std::unique_ptr<Command>> &bQueue,
               Queue<std::vector<std::unique_ptr<GameObject>>> &nbQueue) : m_window("SDL2pp demo",
                                                                                    SDL_WINDOWPOS_UNDEFINED,
                                                                                    SDL_WINDOWPOS_UNDEFINED,
                                                                                    WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                                    SDL_WINDOW_RESIZABLE),
                                                                           m_renderer(m_window, -1,
                                                                                      SDL_RENDERER_ACCELERATED),
                                                                           m_beams(beams), m_bQueue(bQueue),
                                                                           m_nbQueue(nbQueue) {
    m_running = true;
}

void Engine::events() {
    m_input.listen();
    if (m_input.closed()) {
        m_running = false;
    }
}

void Engine::update() {
    float dt = m_timer.getDeltaTime();
    while (m_nbQueue.move_try_pop(m_gameObjects)) {}
    for (const auto &m_gameObject: m_gameObjects) {
        m_gameObject->update(dt, m_input, m_bQueue, m_camera);
    }

}

void Engine::render() {
    m_renderer.Clear();
    m_textureManager.draw("bg", 0, 0, 1920, 1080, m_renderer, SDL_FLIP_NONE);

    for (Beam beams: m_beams) {
        beams.draw(m_renderer, m_textureManager);
    }

    for (const auto &m_gameObject: m_gameObjects) {
        m_gameObject->draw(m_renderer, m_textureManager, m_camera);
    }

    m_renderer.Present();
}

void Engine::init() {
    m_textureManager.parseTexture("../Client/resources/assets/textures.yaml", m_renderer);
}

bool Engine::running() const {
    return m_running;
}

void Engine::tick() {
    m_timer.tick();
}