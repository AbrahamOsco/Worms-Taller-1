//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"
#include "../gameObject/gameInfo/GameInfo.h"
#include "../utils/Constants.h"
#include "../gameObject/crosshair/Crosshair.h"
#include "../gameObject/projectile/Projectile.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue)
        : m_protocol(protocol), m_queue(queue), m_running(true) {}

void ReceiverThread::run() {

    while (m_running) {
        std::vector<std::unique_ptr<GameObject>> gameObjects;

        SnapShot snapShot = m_protocol.recvASnapShot();
        std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
        WeaponSightDTO weaponSightDto = snapShot.getWeaponSightDto();
        ProjectilesDTO projectilesDto = snapShot.getProjectilesDto();

        std::vector<ProjectileDTO> projectiles =  projectilesDto.getProjectilesDto();
        for(const ProjectileDTO &projectileDto : projectiles) {
            std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectileDto.getPositionX(), projectileDto.getPositionY(), projectileDto.getTypeProjectil());
            gameObjects.push_back(std::move(projectile));
        }


        WeaponInventory weaponInventory;
        WeaponsDTO weaponsDto = snapShot.getWeaponsDto();
        std::vector<WeaponDTO> weapons = weaponsDto.getWeapons();

        for (const WormDTO &wormDto: wormsDto) {
            std::unique_ptr<Worm> worm = std::make_unique<Worm>(static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()), wormDto.getHpWorm(),
                                                                wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(), weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight());
            gameObjects.push_back(std::move(worm));
        }


        for (const WeaponDTO &weaponDto: weapons) {
            int ammoCount = -1;
            if (weaponDto.getTypeMunition() == TypeMunition::NO_INFINITE) {
                ammoCount = static_cast<int>(weaponDto.getMunition());
            }
            Weapon weapon(weaponDto.getTypeWeapon(), ammoCount, weaponsDto.getWeaponCurrent());
            weaponInventory.addWeapon(weapon);
        }

        PlayersInfo playersInfo;
        PlayersDTO playersDto = snapShot.getPlayersDto();
        std::vector<PlayerDTO> players = playersDto.getPlayersDTO();
        for (const PlayerDTO &playerDto: players) {
            PlayerInfo playerInfo(static_cast<int>(playerDto.getIdPlayer()), playerDto.getNamePlayer(), static_cast<int>(playerDto.getTotalHpWorms()));
            playersInfo.addPlayer(playerInfo);
        }

        WindInfo wind(10, Direction::RIGHT);
        std::string currentTurn = "Pepe";
        gameObjects.push_back(
                std::make_unique<GameInfo>(playersInfo, weaponInventory, wind, currentTurn, 10, true));

        std::unique_ptr<Crosshair> crosshair = std::make_unique<Crosshair>(static_cast<int>(weaponSightDto.getPositionXSight()), static_cast<int>(weaponSightDto.getPositionYSight()), weaponSightDto.getTypeSight());
        gameObjects.push_back(std::move(crosshair));

        m_queue.move_try_push(std::move(gameObjects));
    }
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
