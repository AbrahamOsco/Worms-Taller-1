//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"
#include "../gameObject/gameInfo/GameInfo.h"
#include "../utils/Constants.h"
#include "../gameObject/crosshair/Crosshair.h"
#include "../gameObject/projectile/Projectile.h"
#include "../exception/ClosedServer.h"
#include "../gameObject/worm/WormNoWeapon.h"
#include "../gameObject/worm/WormRangedWeapon.h"
#include "../gameObject/worm/WormMeleeWeapon.h"
#include "../gameObject/worm/WormGuidedWeapon.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue,
                               std::atomic<bool> &running)
        : m_protocol(protocol), m_queue(queue), m_running(running) {}

void ReceiverThread::run() {

    while (m_running) {
        try {
            std::vector<std::unique_ptr<GameObject>> gameObjects;
            SnapShot snapShot = m_protocol.recvSnapShot();
            std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
            WeaponSightDTO weaponSightDto = snapShot.getWeaponSightDto();
            ProjectilesDTO projectilesDto = snapShot.getProjectilesDto();
            TurnDTO turnDto = snapShot.getTurnDto();

            bool isMyTurn = false;
            if (turnDto.getTextTurn() == "Es tu turno") {
                isMyTurn = true;
            }


            std::vector<ProjectileDTO> projectiles = projectilesDto.getProjectilesDto();
            for (const ProjectileDTO &projectileDto: projectiles) {
                std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectileDto.getPositionX(),
                                                                                      projectileDto.getPositionY(),
                                                                                      projectileDto.getTypeProjectil());
                gameObjects.push_back(std::move(projectile));
            }


            WeaponInventory weaponInventory;
            WeaponsDTO weaponsDto = snapShot.getWeaponsDto();
            std::vector<WeaponDTO> weapons = weaponsDto.getWeapons();

            for (const WormDTO &wormDto: wormsDto) {

                if (wormDto.getWeaponCurrent() == TypeWeapon::NONE_WEAPON) {
                    std::unique_ptr<WormNoWeapon> worm = std::make_unique<WormNoWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                            static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                            wormDto.getHpWorm(),
                            wormDto.getDirectionLook(), wormDto.getTypeFocus(), wormDto.getMoveWorm());
                    gameObjects.push_back(std::move(worm));
                } else if (wormDto.getWeaponCurrent() == TypeWeapon::BAZOOKA) {
                    std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                            static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                            wormDto.getHpWorm(),
                            wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                            wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                            weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight());
                    gameObjects.push_back(std::move(worm));
                } else if (wormDto.getWeaponCurrent() == TypeWeapon::BASEBALL_BAT) {
                    std::unique_ptr<WormMeleeWeapon> worm = std::make_unique<WormMeleeWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                            static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                            wormDto.getHpWorm(),
                            wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                            wormDto.getMoveWorm(), wormDto.getWeaponCurrent());
                    gameObjects.push_back(std::move(worm));
                } else if (wormDto.getWeaponCurrent() == TypeWeapon::TELEPORT) {
                    std::unique_ptr<WormGuidedWeapon> worm = std::make_unique<WormGuidedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                            static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                            wormDto.getHpWorm(),
                            wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                            wormDto.getMoveWorm(), wormDto.getWeaponCurrent());
                    gameObjects.push_back(std::move(worm));
                }

            }


            for (const WeaponDTO &weaponDto: weapons) {
                int ammoCount = -1;
                if (weaponDto.getTypeMunition() == TypeMunition::NO_INFINITE) {
                    ammoCount = static_cast<int>(weaponDto.getMunition());
                }
                WeaponIcon weaponIcon(weaponDto.getTypeWeapon(), ammoCount, weaponsDto.getWeaponCurrent(), isMyTurn);
                weaponInventory.addWeapon(weaponIcon);
            }

            PlayersInfo playersInfo;
            PlayersDTO playersDto = snapShot.getPlayersDto();
            std::vector<PlayerDTO> players = playersDto.getPlayersDTO();
            for (const PlayerDTO &playerDto: players) {
                PlayerInfo playerInfo(static_cast<int>(playerDto.getIdPlayer()), playerDto.getNamePlayer(),
                                      static_cast<int>(playerDto.getTotalHpWorms()));
                playersInfo.addPlayer(playerInfo);
            }

            WindInfo wind(10, Direction::RIGHT);
            gameObjects.push_back(
                    std::make_unique<GameInfo>(playersInfo, weaponInventory, wind, turnDto.getTextTurn(),
                                               turnDto.getTimeLeft()));

            std::unique_ptr<Crosshair> crosshair = std::make_unique<Crosshair>(
                    static_cast<int>(weaponSightDto.getPositionXSight()),
                    static_cast<int>(weaponSightDto.getPositionYSight()), weaponSightDto.getTypeSight());
            gameObjects.push_back(std::move(crosshair));

            m_queue.move_try_push(std::move(gameObjects));
        } catch (const ClosedServer &closedServer) {
            m_running = false;
        }
    }
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
