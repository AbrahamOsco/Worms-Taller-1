//
// Created by riclui on 24/10/23.
//

#include "Engine.h"
#include "../gameObject/worm/Worm.h"
#include "../utils/Constants.h"
#include "../gameObject/beam/Beam.h"
#include "../command/MoveRight.h"
#include "../command/MoveLeft.h"

Engine::Engine(std::vector<Beam>& beams, Queue<std::unique_ptr<Command>>& bQueue, Queue<std::vector<std::unique_ptr<GameObject>>>& nbQueue) : m_pWindow("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
                             0),
                   m_pRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED), m_beams(beams), m_bQueue(bQueue), m_nbQueue(nbQueue) {
    m_bRunning = true;
}

void Engine::events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_bRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RIGHT) {
                std::unique_ptr<Command> command(new MoveRight()); // Comando para mover a la derecha
                m_bQueue.move_push(std::move(command));
            } else if (event.key.keysym.sym == SDLK_LEFT) {
                std::unique_ptr<Command> command(new MoveLeft()); // Comando para mover a la izquierda
                m_bQueue.move_push(std::move(command));
            }
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

    m_buttons.draw(m_pRenderer, m_textureManager);

    m_pRenderer.Present();
}

void Engine::init() {
    m_textureManager.parseTexture("../Client/resources/assets/textures.yaml", m_pRenderer);
    m_buttons.addButton(std::make_unique<Button>("air_attack_icon"));
    m_buttons.addButton(std::make_unique<Button>("banana_icon"));
    m_buttons.addButton(std::make_unique<Button>("bat_icon"));
    m_buttons.addButton(std::make_unique<Button>("bazooka_icon"));
    m_buttons.addButton(std::make_unique<Button>("dynamite_icon"));
    m_buttons.addButton(std::make_unique<Button>("green_grenade_icon"));
    m_buttons.addButton(std::make_unique<Button>("holy_grenade_icon"));
    m_buttons.addButton(std::make_unique<Button>("mortar_icon"));
    m_buttons.addButton(std::make_unique<Button>("red_grenade_icon"));
    m_buttons.addButton(std::make_unique<Button>("teleportation_icon"));
}

bool Engine::running() const {
    return m_bRunning;
}

void Engine::tick() {
    m_timer.tick();
}