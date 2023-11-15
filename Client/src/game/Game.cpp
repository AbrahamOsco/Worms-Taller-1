//
// Created by riclui on 31/10/23.
//

#include "Game.h"
#include "../core/Engine.h"
#include "../../../Common/Queue/Queue.h"
#include "../command/Command.h"
#include "../thread/ReceiverThread.h"
#include "../thread/SenderThread.h"
#include "../rateController/RateController.h"

Game::Game(Socket& skt) : m_protocol(skt){}

void Game::loadMap() {
    StageDTO stageDto;
    stageDto = m_protocol.recvStageDTO();
    std::vector<BeamDTO> beams = stageDto.getBeams();
    for (const BeamDTO& beamDto: beams) {
        m_beams.emplace_back(beamDto.getXCenter(), beamDto.getYCenter(), static_cast<Angle>(beamDto.getAngle()), beamDto.getTypeBeam());
    }
}

void Game::run() {
    Queue<std::vector<std::unique_ptr<GameObject>>> nbQueue;
    Queue<std::unique_ptr<Command>> bQueue;

    ReceiverThread receiverThread(m_protocol, nbQueue);
    SenderThread senderThread(m_protocol, bQueue);

    receiverThread.start();
    senderThread.start();

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::SDLTTF ttf;
    Engine engine(m_beams, bQueue, nbQueue);
    engine.init();

    RateController frameRate(60);
    frameRate.start();

    while (engine.running()) {
        engine.events();
        engine.update();
        engine.render();
        engine.tick();
        frameRate.finish();
    }

    senderThread.stop();
    receiverThread.stop();
    senderThread.join();
    receiverThread.join();
}
