//
// Created by riclui on 31/10/23.
//

#include "ReceiverThread.h"
#include "../gameObject/worm/Worm.h"
#include "../gameObject/gameInfo/GameInfo.h"
#include "../gameObject/crosshair/Crosshair.h"
#include "../gameObject/projectile/Projectile.h"
#include "../exception/ClosedServer.h"
#include "../gameObject/worm/WormNoWeapon.h"
#include "../gameObject/worm/WormRangedWeapon.h"
#include "../gameObject/worm/WormMeleeWeapon.h"
#include "../gameObject/worm/WormGuidedWeapon.h"
#include "../gameObject/gameState/PlayerState.h"
#include "../gameObject/provision/Provision.h"

ReceiverThread::ReceiverThread(ClientProtocol &protocol, Queue<std::vector<std::unique_ptr<GameObject>>> &queue,
                               std::atomic<bool> &running)
        : m_protocol(protocol), m_queue(queue), m_running(running) {}

void ReceiverThread::run() {
    size_t pastCountWorm = 0;
    size_t currentCountWorm = 0;
    while (m_running) {
        try {
            std::vector<std::unique_ptr<GameObject>> gameObjects;

            SnapShot snapShot = m_protocol.recvSnapShot();
            if (snapShot.getTypeSnapShot()  == GameState::GAME_PROGRESS) {
                processGameProgressSnapshot(snapShot, gameObjects, pastCountWorm, currentCountWorm);


            } else {
                processNonGameProgressSnapshot(snapShot, gameObjects);
            }
            m_queue.move_try_push(std::move(gameObjects));
        } catch (const ClosedServer &closedServer) {
            m_running = false;
        }
    }
}

void ReceiverThread::processNonGameProgressSnapshot(const SnapShot &snapShot,
                                                    std::vector<std::unique_ptr<GameObject>> &gameObjects) const {
    GameState gameState = snapShot.getTypeSnapShot();
    TypeResult typeResult = snapShot.getEndGameDto().getTypeResult();
    std::unique_ptr<PlayerState> playerState = std::make_unique<PlayerState>(gameState, typeResult);
    gameObjects.push_back(std::move(playerState));
}

void ReceiverThread::processGameProgressSnapshot(const SnapShot &snapShot, std::vector<std::unique_ptr<GameObject>> &gameObjects,
                                                 size_t pastCountWorm, size_t currentCountWorm) const {
    std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
    WeaponSightDTO weaponSightDto = snapShot.getWeaponSightDto();
    ProjectilesDTO projectilesDto = snapShot.getProjectilesDto();
    WeaponsDTO weaponsDto = snapShot.getWeaponsDto();
    TurnDTO turnDto = snapShot.getTurnDto();

    bool isMyTurn = false;
    if (turnDto.getTextTurn() == "Es tu turno") {
        isMyTurn = true;
    }

    currentCountWorm = wormsDto.size();
    bool death = false;
    if (currentCountWorm != pastCountWorm && pastCountWorm != 0) {
        death = true;
    }

    std::vector<ProjectileDTO> projectiles = projectilesDto.getProjectilesDto();
    for (const ProjectileDTO &projectileDto: projectiles) {
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectileDto.getPositionX(),
                                                                              projectileDto.getPositionY(),
                                                                              projectileDto.getTypeProjectil(), projectileDto.getTypeFocus(), projectileDto.getTypeExplode());
        gameObjects.push_back(std::move(projectile));
    }


    WeaponInventory weaponInventory;
    std::vector<WeaponDTO> weapons = weaponsDto.getWeapons();

    for (const WormDTO &wormDto: wormsDto) {

        if (wormDto.getWeaponCurrent() == NONE_WEAPON) {
            std::unique_ptr<WormNoWeapon> worm = std::make_unique<WormNoWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                wormDto.getHpWorm(),
                                                                                wormDto.getDirectionLook(), wormDto.getTypeFocus(), wormDto.getMoveWorm(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == BAZOOKA) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                        static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                        wormDto.getHpWorm(),
                                                                                        wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                                        wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                                                                                        weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == BASEBALL_BAT) {
            std::unique_ptr<WormMeleeWeapon> worm = std::make_unique<WormMeleeWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                      static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                      wormDto.getHpWorm(),
                                                                                      wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                                      wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                                                                                      weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == TELEPORT) {
            std::cout << "focus: " << wormDto.getTypeFocus() << std::endl;
            std::unique_ptr<WormGuidedWeapon> worm = std::make_unique<WormGuidedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                        static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                        wormDto.getHpWorm(),
                                                                                        wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                                        wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == AIR_ATTACK) {
            std::unique_ptr<WormGuidedWeapon> worm = std::make_unique<WormGuidedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                        static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                        wormDto.getHpWorm(),
                                                                                        wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                                        wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == MORTAR) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(
                    static_cast<int>(wormDto.getIdPlayer()),
                    static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                    wormDto.getHpWorm(),
                    wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                    wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                    weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == GREEN_GRENADE) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(
                    static_cast<int>(wormDto.getIdPlayer()),
                    static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                    wormDto.getHpWorm(),
                    wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                    wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                    weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == RED_GRENADE) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(
                    static_cast<int>(wormDto.getIdPlayer()),
                    static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                    wormDto.getHpWorm(),
                    wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                    wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                    weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == BANANA) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(
                    static_cast<int>(wormDto.getIdPlayer()),
                    static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                    wormDto.getHpWorm(),
                    wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                    wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                    weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == HOLY_GRENADE) {
            std::unique_ptr<WormRangedWeapon> worm = std::make_unique<WormRangedWeapon>(
                    static_cast<int>(wormDto.getIdPlayer()),
                    static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                    wormDto.getHpWorm(),
                    wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                    wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                    weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        } else if (wormDto.getWeaponCurrent() == DYNAMITE_HOLDER) {
            std::unique_ptr<WormMeleeWeapon> worm = std::make_unique<WormMeleeWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                                                      static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                                                      wormDto.getHpWorm(),
                                                                                      wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                                                      wormDto.getMoveWorm(), wormDto.getWeaponCurrent(), weaponSightDto.getPositionXSight(),
                                                                                      weaponSightDto.getPositionYSight(), weaponSightDto.getTypeSight(), isMyTurn);
            gameObjects.push_back(std::move(worm));
        }

    }

    std::vector<ProvisionDTO> provisions = snapShot.getVecProvisionDto();
    for (const ProvisionDTO &provisionDto: provisions) {
        gameObjects.push_back(std::make_unique<Provision>(static_cast<int>(provisionDto.getPositionX()), static_cast<int>(provisionDto.getPositionY()), provisionDto.getTypeEffect(), provisionDto.getTypeContact()));
    }

    for (const WeaponDTO &weaponDto: weapons) {
        WeaponIcon weaponIcon(weaponDto.getTypeWeapon(), static_cast<int>(weaponDto.getMunition()), weaponDto.getTypeMunition(), weaponsDto.getWeaponCurrent(), isMyTurn);
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

    GameState gameState = snapShot.getTypeSnapShot();
    TypeResult typeResult = snapShot.getEndGameDto().getTypeResult();

    WindInfo wind(static_cast<int>(snapShot.getTurnDto().getValueWind()), snapShot.getTurnDto().getTypeWind());

    gameObjects.push_back(
            std::make_unique<GameInfo>(playersInfo, weaponInventory, wind, gameState, typeResult,turnDto.getTextTurn(),
                                       turnDto.getTimeLeft(), death));

    pastCountWorm = wormsDto.size();
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}
