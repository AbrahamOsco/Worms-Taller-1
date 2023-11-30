//
// Created by riclui on 24/10/23.
//

#include <utility>
#include "Engine.h"
#include "../gameObject/worm/Worm.h"
#include "../utils/Constants.h"
#include "../gameObject/beam/Beam.h"
#include "../command/RightCmd.h"
#include "../command/LeftCmd.h"
#include "../command/CloseCmd.h"

Engine::Engine(std::vector<Beam> &beams, const std::string &background,
                Queue<std::unique_ptr<Command>> &bQueue,
                Queue<std::vector<std::unique_ptr<GameObject>>> &nbQueue, std::atomic<bool>& running) :
                m_window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                WINDOW_WIDTH, WINDOW_HEIGHT, 0),
                m_renderer(m_window, -1, SDL_RENDERER_ACCELERATED),
                m_beams(beams), m_background(background), m_bQueue(bQueue),
                m_nbQueue(nbQueue), m_running(running), m_timer() {}

void Engine::events() {
    m_input.listen();
    if (m_input.closed()) {
        std::unique_ptr<Command> command(new CloseCmd());
        m_bQueue.move_push(std::move(command));
        m_running = false;
    }
}

void Engine::update() {
    while (m_nbQueue.move_try_pop(m_gameObjects)) {}
    for (const auto &m_gameObject : m_gameObjects) {
        m_gameObject->update(m_input, m_bQueue, m_camera, m_soundManager);
    }
    m_volume.update(m_input, m_bQueue, m_camera, m_soundManager);
    m_camera.update();
}

void Engine::render() {
    m_renderer.Clear();
    m_textureManager.draw(m_background, 0, - m_camera.getPosition().GetY(), 1920, 1080, m_renderer, SDL_FLIP_NONE);

    for (Beam beams : m_beams) {
        beams.draw(m_renderer, m_textureManager, m_camera);
    }

    for (const auto &m_gameObject : m_gameObjects) {
        m_gameObject->draw(m_renderer, m_textureManager, m_camera);
    }
    m_volume.draw(m_renderer, m_textureManager, m_camera);
    m_renderer.Present();
}

void Engine::init() {
    m_textureManager.parseTexture("../Client/resources/assets/textures.yaml", m_renderer);
    m_soundManager.parseSounds("../Client/resources/sounds/sounds.yaml");
    m_soundManager.playMusic("background_music");
}

bool Engine::running() const {
    return m_running;
}

void Engine::tick() {
    m_timer.tick();
}
