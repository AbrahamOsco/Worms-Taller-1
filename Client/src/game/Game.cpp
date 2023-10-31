//
// Created by riclui on 31/10/23.
//

#include "Game.h"
#include "../core/Engine.h"


Game::Game(const char *ip, const char *port) : skt(ip, port), protocol(skt){}

void Game::loadMap() {
    //protocol.recvStageDTO();
    m_beams.push_back(std::make_unique<Beam>(0, 0, ANGLE_0, SHORT_BEAM));
    m_beams.push_back(std::make_unique<Beam>(200, 200, ANGLE_10, SHORT_BEAM));

    m_beams.push_back(std::make_unique<Beam>(400, 400, ANGLE_20, LONG_BEAM));
    m_beams.push_back(std::make_unique<Beam>(600, 600, ANGLE_0, LONG_BEAM));
}

void Game::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Engine engine(m_beams);
    engine.init();
    while (engine.running()) {
        engine.events();
        engine.update();
        engine.render();
        engine.tick();
    }
}
