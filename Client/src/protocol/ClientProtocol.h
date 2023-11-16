#ifndef PROTOCOLO_CLIENT_PROTOCOL_H
#define PROTOCOLO_CLIENT_PROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/DTO/DTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayersDTO.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/SnapShot.h"
#include "../../../Common/DTO/WeaponsDTO.h"
#include "../../../Common/DTO/WeaponSightDTO.h"

class ClientProtocol : public Protocol {

public:
    explicit ClientProtocol(Socket& skt);

    void sendInitialStateDTO(const InitialStateDTO& initialStateDto);

    void sendResponseInitialStateDTO(const ResponseInitialStateDTO& responseInitial);

    ResolverInitialDTO recvResolverInitialDTO();

    RoomDTO recvRoom();

    StageDTO recvStageDTO();

    BeamDTO recvBeamDTO();

    PlayersDTO recvPlayersDTO();

    PlayerDTO recvAPlayerDTO();

    void sendCommandDTO(const CommandDTO& commandDto);

    SnapShot recvASnapShot();

    WormDTO recvAWormDTO();

    WeaponsDTO recvWeaponsDTO();

    WeaponDTO recvAWeaponDTO();

    WeaponSightDTO recvWeaponSightDTO();

    ~ClientProtocol() = default;

    ProjectileDTO recvAProjectileDTO();

    ProjectilesDTO recvProjectilesDTO();

    TurnDTO recvTurnDTO();
};


#endif //PROTOCOLO_CLIENT_PROTOCOL_H
