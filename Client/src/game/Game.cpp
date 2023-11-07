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
        //std::cout << '(' << beamDto.getXCenter() * 60 << ',' << 1080 - beamDto.getYCenter() * 60 << ')' << std::endl;
        m_beams.emplace_back(beamDto.getXCenter() * 60,1080 - beamDto.getYCenter() * 60, static_cast<Angle>(beamDto.getAngle()), beamDto.getTypeBeam());
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
    Engine engine(m_beams, bQueue, nbQueue);
    engine.init();
    while (engine.running()) {
        engine.events();
        engine.update();
        engine.render();
        engine.tick();
    }

    senderThread.stop();
    receiverThread.stop();
    senderThread.join();
    receiverThread.join();
}
