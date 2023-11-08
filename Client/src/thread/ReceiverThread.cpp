//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"
#include "../gameObject/button/Button.h"
#include "../buttonManager/ButtonManager.h"
#include "../gameObject/turn/Turn.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue) : m_protocol(protocol), m_queue(queue), m_running(true) {}

void ReceiverThread::run() {

    while (m_running) {
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        LoaderParams params1(512, 384, 60, 60, "player");

        SnapShot snapShot;
        snapShot = m_protocol.recvASnapShot();
        std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
        for (const WormDTO& wormDto: wormsDto) {
            std::cout << wormDto.getMoveWorm() << std::endl;
            LoaderParams loaderParams((int)wormDto.getPositionX(), 1080 - (int)wormDto.getPositionY(), 60, 60, "player");
            std::unique_ptr<Worm> worm = std::make_unique<Worm>(loaderParams, wormDto.getHpWorm() ,wormDto.getDirectionLook(), wormDto.getTypeFocus(), wormDto.getMoveWorm());
            gameObjects.push_back(std::move(worm));
        }

        gameObjects.push_back(std::make_unique<Turn>(true));

        std::vector<Button> buttons;
        buttons.emplace_back("air_attack_icon");
        buttons.emplace_back("banana_icon");
        buttons.emplace_back("bat_icon");
        buttons.emplace_back("bazooka_icon");
        buttons.emplace_back("dynamite_icon");
        buttons.emplace_back("green_grenade_icon");
        buttons.emplace_back("holy_grenade_icon");
        buttons.emplace_back("mortar_icon");
        buttons.emplace_back("red_grenade_icon");
        buttons.emplace_back("teleportation_icon");

        gameObjects.push_back(std::make_unique<ButtonManager>(params1, std::move(buttons)));
        m_queue.move_try_push(std::move(gameObjects));
    }
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
