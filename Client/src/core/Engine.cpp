//
// Created by riclui on 24/10/23.
//

#include "Engine.h"
#include "../gameObject/player/Player.h"
#include "../gameObject/icons/Icon.h"
#include "../gameObject/icons/AirAttackIcon.h"
#include "../gameObject/icons/BananaIcon.h"
#include "../gameObject/icons/BatIcon.h"

Engine::Engine() : m_pWindow("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768,
                             0),
                   m_pRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED) {
    m_bRunning = true;
}

void Engine::render() {
    m_pRenderer.Clear();
    m_textureManager.draw("bg", 0, 0, 1920, 1080, m_pRenderer,SDL_FLIP_NONE);

    for (const auto &m_gameObject: m_gameObjects) {
        m_gameObject->draw(m_pRenderer, m_textureManager);
    }

    m_pRenderer.Present();
}

void Engine::update() {
    float dt = m_timer.getDeltaTime();
    for (const auto & m_gameObject : m_gameObjects) {
        m_gameObject->update(dt);
    }
}

void Engine::events() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Engine::init() {
    m_textureManager.parseTexture("../Client/resources/assets/textures.yaml", m_pRenderer);
    LoaderParams params1(0, 0, 60, 60, "player");
    m_gameObjects.push_back(std::make_unique<Player>(params1));
    m_gameObjects.push_back(std::make_unique<AirAttackIcon>());
    m_gameObjects.push_back(std::make_unique<BananaIcon>());
    m_gameObjects.push_back(std::make_unique<BatIcon>());
}

bool Engine::running() const {
    return m_bRunning;
}

void Engine::tick() {
    m_timer.tick();
}