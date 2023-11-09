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

        LoaderParams params(0, 0, WINDOW_WIDTH, 20, "arrow_no");

        PlayersInfo playersInfo;
        PlayerInfo playerInfo1(0, "Agustin", 80);
        PlayerInfo playerInfo2(1, "Juan", 80);
        playersInfo.addPlayer(playerInfo1);
        playersInfo.addPlayer(playerInfo2);

        WeaponInventory weaponInventory;
        Weapon weapon1("air_attack_icon", 10);
        Weapon weapon2("banana_icon", 10);
        Weapon weapon3("bat_icon", 10);
        Weapon weapon4("bazooka_icon", 10);
        Weapon weapon5("dynamite_icon", 10);
        Weapon weapon6("green_grenade_icon", 10);
        Weapon weapon7("holy_grenade_icon", 10);
        Weapon weapon8("mortar_icon", 10);
        Weapon weapon9("red_grenade_icon", 10);
        Weapon weapon10("teleportation_icon", 10);
        weaponInventory.addWeapon(weapon1);
        weaponInventory.addWeapon(weapon2);
        weaponInventory.addWeapon(weapon3);
        weaponInventory.addWeapon(weapon4);
        weaponInventory.addWeapon(weapon5);
        weaponInventory.addWeapon(weapon6);
        weaponInventory.addWeapon(weapon7);
        weaponInventory.addWeapon(weapon8);
        weaponInventory.addWeapon(weapon9);
        weaponInventory.addWeapon(weapon10);

        WindInfo wind(params, 10, Direction::RIGHT);
        std::string currentTurn = "Pepe";
        gameObjects.push_back(
                std::make_unique<GameInfo>(params, playersInfo, weaponInventory, wind, currentTurn, true));
        m_queue.move_try_push(std::move(gameObjects));
    }
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
