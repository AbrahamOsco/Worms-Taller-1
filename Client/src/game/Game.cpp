//
// Created by riclui on 31/10/23.
//

#include <vector>
#include <memory>
#include <SDL_mixer.h>
#include <SDL2pp/Chunk.hh>
#include "Game.h"
#include "../core/Engine.h"
#include "../../../Common/Queue/Queue.h"
#include "../command/Command.h"
#include "../thread/ReceiverThread.h"
#include "../thread/SenderThread.h"
#include "../../../Common/rateController/RateController.h"

Game::Game(Socket& skt) : m_protocol(skt), m_running(true) {}

void Game::loadMap() {
    StageDTO stageDto;
    stageDto = m_protocol.recvStageDTO();
    std::vector<BeamDTO> beams = stageDto.getBeams();
    for (const BeamDTO& beamDto : beams) {
        m_beams.emplace_back(beamDto.getXCenter(), beamDto.getYCenter(),
                            static_cast<Angle>(beamDto.getAngle()), beamDto.getTypeBeam());
    }
    m_background = stageDto.getBackground();
}

void Game::run() {
    Queue<std::vector<std::unique_ptr<GameObject>>> nbQueue;
    Queue<std::unique_ptr<Command>> bQueue;

    ReceiverThread receiverThread(m_protocol, nbQueue, m_running);
    SenderThread senderThread(m_protocol, bQueue, m_running);

    receiverThread.start();
    senderThread.start();

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    const int audioFrequency = 44100;
    const Uint16 audioFormat = MIX_DEFAULT_FORMAT;
    const int audioChannels = 2;
    const int audioChunkSize = 2048;

    if (Mix_OpenAudio(audioFrequency, audioFormat, audioChannels, audioChunkSize) < 0) {
        std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        return;
    }

    SDL2pp::SDLTTF ttf;
    Engine engine(m_beams, m_background, bQueue, nbQueue, m_running);
    engine.init();

    RateController frameRate(19);
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
