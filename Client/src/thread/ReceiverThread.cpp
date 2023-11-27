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
    size_t currentCountWorm;
    while (m_running) {
        try {
            std::vector<std::unique_ptr<GameObject>> gameObjects;

            SnapShot snapShot = m_protocol.recvSnapShot();
            if (snapShot.getTypeSnapShot()  == GameState::GAME_PROGRESS) {
                currentCountWorm = snapShot.getWormsDto().size();
                processGameProgressSnapshot(snapShot, gameObjects, pastCountWorm, currentCountWorm);
                pastCountWorm = currentCountWorm;

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
                                                 size_t pastCountWorm, size_t currentCountWorm) {
    std::vector<WormDTO> wormsDto = snapShot.getWormsDto();
    WeaponSightDTO weaponSightDto = snapShot.getWeaponSightDto();
    ProjectilesDTO projectilesDto = snapShot.getProjectilesDto();
    WeaponsDTO weaponsDto = snapShot.getWeaponsDto();
    TurnDTO turnDto = snapShot.getTurnDto();

    bool isMyTurn = false;
    if (turnDto.getTextTurn() == "Es tu turno") {
        isMyTurn = true;
    }

    bool death = false;
    if (currentCountWorm != pastCountWorm && pastCountWorm != 0) {
        death = true;
    }

    WeaponInventory weaponInventory;
    std::vector<WeaponDTO> weapons = weaponsDto.getWeapons();

    processWorms(wormsDto, weaponSightDto, snapShot.getTurnDto().getTextTurn() == "Es tu turno", gameObjects);
    processProjectiles(snapShot.getProjectilesDto(), gameObjects);

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
}

void ReceiverThread::processWorms(std::vector<WormDTO> &wormsDto, const WeaponSightDTO &weaponSightDto, bool isMyTurn,
                                  std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    for (const WormDTO& wormDto : wormsDto) {
        std::unique_ptr<Worm> worm = createWormObject(wormDto, weaponSightDto, isMyTurn);
        gameObjects.push_back(std::move(worm));
    }
}

std::unique_ptr<Worm>
ReceiverThread::createWormObject(const WormDTO &wormDto, const WeaponSightDTO &weaponSightDto, bool isMyTurn) {
    TypeWeapon currentWeapon = wormDto.getWeaponCurrent();
    TypeSight sightType = weaponSightDto.getTypeSight();

    if (currentWeapon == NONE_WEAPON) {
        return std::make_unique<WormNoWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                              static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                              wormDto.getHpWorm(),
                                              wormDto.getDirectionLook(), wormDto.getTypeFocus(), wormDto.getMoveWorm(), isMyTurn);

    } else if (currentWeapon == BAZOOKA || currentWeapon == MORTAR || currentWeapon == GREEN_GRENADE ||
               currentWeapon == RED_GRENADE || currentWeapon == BANANA || currentWeapon == HOLY_GRENADE) {
        return std::make_unique<WormRangedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                  static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                  wormDto.getHpWorm(),
                                                  wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                  wormDto.getMoveWorm(), currentWeapon, weaponSightDto.getPositionXSight(),
                                                  weaponSightDto.getPositionYSight(), sightType, isMyTurn);

    } else if (currentWeapon == BASEBALL_BAT || currentWeapon == DYNAMITE_HOLDER) {
        return std::make_unique<WormMeleeWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                 static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                 wormDto.getHpWorm(),
                                                 wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                 wormDto.getMoveWorm(), currentWeapon, weaponSightDto.getPositionXSight(),
                                                 weaponSightDto.getPositionYSight(), sightType, isMyTurn);

    } else if (currentWeapon == TypeWeapon::TELEPORT || currentWeapon == TypeWeapon::AIR_ATTACK) {
        return std::make_unique<WormGuidedWeapon>(static_cast<int>(wormDto.getIdPlayer()),
                                                  static_cast<int>(wormDto.getPositionX()), static_cast<int>(wormDto.getPositionY()),
                                                  wormDto.getHpWorm(),
                                                  wormDto.getDirectionLook(), wormDto.getTypeFocus(),
                                                  wormDto.getMoveWorm(), currentWeapon, isMyTurn);
    }

    return nullptr;
}

void ReceiverThread::stop() {
    m_running = false;
    //m_protocol.stop();
}

void ReceiverThread::processProjectiles(const ProjectilesDTO &projectilesDto,
                                        std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    std::vector<ProjectileDTO> projectiles = projectilesDto.getProjectilesDto();
    for (const ProjectileDTO &projectileDto: projectiles) {
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(projectileDto.getPositionX(),
                                                                              projectileDto.getPositionY(),
                                                                              projectileDto.getTypeProjectil(), projectileDto.getTypeFocus(), projectileDto.getTypeExplode());
        gameObjects.push_back(std::move(projectile));
    }
}
