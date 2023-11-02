//
// Created by riclui on 31/10/23.
//

#include "Game.h"
#include "../core/Engine.h"
#include "../../../Common/Queue/Queue.h"
#include "../command/Command.h"
#include "../thread/ReceiverThread.h"
#include "../thread/SenderThread.h"

Game::Game(Socket& skt) : m_protocol(skt){}

void Game::loadMap() {
    StageDTO stageDto;
    stageDto = m_protocol.recvStageDTO();
    std::vector<BeamDTO> beams = stageDto.getBeams();
    for (const BeamDTO& beamDto: beams) {
        m_beams.emplace_back(beamDto.getXCenter(),beamDto.getYCenter(), static_cast<Angle>(beamDto.getAngle()), beamDto.getTypeBeam());
    }


    /*m_beams.emplace_back(0, 0, ANGLE_0, SHORT_BEAM);
    m_beams.emplace_back(200, 200, ANGLE_10, SHORT_BEAM);

    m_beams.emplace_back(400, 400, ANGLE_20, LONG_BEAM);
    m_beams.emplace_back(600, 600, ANGLE_0, LONG_BEAM);*/
}

void Game::run() {
    //Queue<std::vector<std::unique_ptr<GameObject>>> nbQueue;
    Queue<std::unique_ptr<Command>> bQueue;

    //ReceiverThread receiverThread(nbQueue, m_protocol);
    SenderThread senderThread(m_protocol, bQueue);
    //receiverThread.start();
    senderThread.start();

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Engine engine(m_beams, bQueue);
    engine.init();
    while (engine.running()) {
        engine.events();
        engine.update();
        engine.render();
        engine.tick();
    }

    senderThread.stop();
    //receiverThread.stop();
    senderThread.join();
    //receiverThread.join();
}
