//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"
#include "../gameObject/gameInfo/GameInfo.h"
#include "../utils/Constants.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue)
        : m_protocol(protocol), m_queue(queue), m_running(true) {}

void ReceiverThread::run() {

    while (m_running) {
        std::vector<std::unique_ptr<GameObject>> gameObjects;


        SnapShot snapShot;
        snapShot = m_protocol.recvASnapShot();
        std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
        for (const WormDTO &wormDto: wormsDto) {
            LoaderParams loaderParams((int) wormDto.getPositionX(), 1080 - (int) wormDto.getPositionY(), 60, 60,
                                      "player");
            std::unique_ptr<Worm> worm = std::make_unique<Worm>(loaderParams, wormDto.getHpWorm(),
                                                                wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                wormDto.getMoveWorm());
            gameObjects.push_back(std::move(worm));
        }

        WeaponInventory weaponInventory;
        WeaponsDTO weaponsDto = snapShot.getWeaponsDto();
        std::vector<WeaponDTO> weapons = weaponsDto.getWeapons();
        for (const WeaponDTO & weaponDto: weapons) {
            int ammoCount = -1;
            if(weaponDto.getTypeMunition() == TypeMunition::NO_INFINITE) {
                ammoCount = (int) weaponDto.getMunition();
            }
            Weapon weapon(weaponDto.getTypeWeapon(), ammoCount);
            weaponInventory.addWeapon(weapon);
        }

        PlayersInfo playersInfo;
        PlayerInfo playerInfo1(0, "Agustin", 80);
        PlayerInfo playerInfo2(1, "Juan", 80);
        playersInfo.addPlayer(playerInfo1);
        playersInfo.addPlayer(playerInfo2);

        WindInfo wind(10, Direction::RIGHT);
        std::string currentTurn = "Pepe";
        gameObjects.push_back(
                std::make_unique<GameInfo>(playersInfo, weaponInventory, wind, currentTurn, 10, true));
        m_queue.move_try_push(std::move(gameObjects));
    }
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
