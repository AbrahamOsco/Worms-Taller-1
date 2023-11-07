//
// Created by riclui on 24/10/23.
//

#include "Engine.h"
#include "../gameObject/worm/Worm.h"
#include "../utils/Constants.h"
#include "../gameObject/beam/Beam.h"
#include "../command/RightCmd.h"
#include "../command/LeftCmd.h"

Engine::Engine(std::vector<Beam>& beams, Queue<std::unique_ptr<Command>>& bQueue, Queue<std::vector<std::unique_ptr<GameObject>>>& nbQueue) : m_pWindow("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                                                                                                        SDL_WINDOW_RESIZABLE),
                   m_pRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED), m_beams(beams), m_bQueue(bQueue), m_nbQueue(nbQueue) {
    m_bRunning = true;
}

void Engine::events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_bRunning = false;
            break;
        }

        for (const auto & m_gameObject : m_gameObjects) {
            m_gameObject->processEvent(event, m_bQueue);
        }
    }
}

void Engine::update() {
    float dt = m_timer.getDeltaTime();
    while (m_nbQueue.move_try_pop(m_gameObjects)){}
    for (const auto & m_gameObject : m_gameObjects) {
        m_gameObject->update(dt);
    }
}

void Engine::render() {
    m_pRenderer.Clear();
    m_textureManager.draw("bg", 0, 0, 1920, 1080, m_pRenderer,SDL_FLIP_NONE);

    for (Beam beams: m_beams) {
        beams.draw(m_pRenderer, m_textureManager);
    }

    for (const auto &m_gameObject: m_gameObjects) {
        m_gameObject->draw(m_pRenderer, m_textureManager);
    }

    m_pRenderer.Present();
}

void Engine::init() {
    m_textureManager.parseTexture("../Client/resources/assets/textures.yaml", m_pRenderer);
}

bool Engine::running() const {
    return m_bRunning;
}

void Engine::tick() {
    m_timer.tick();
}