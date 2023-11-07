#ifndef PROTOCOLO_CLIENT_PROTOCOL_H
#define PROTOCOLO_CLIENT_PROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/DTO/DTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/DTO/StageDTO.h"
#include "../../../Common/DTO/PlayersIniDTO.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/SnapShot.h"

class ClientProtocol : public Protocol {

public:
    explicit ClientProtocol(Socket& skt);

    void sendInitialStateDTO(const InitialStateDTO& initialStateDto);

    void sendResponseInitialStateDTO(const ResponseInitialStateDTO& responseInitial);

    ResolverInitialDTO recvResolverInitialDTO();

    RoomDTO recvRoom();

    StageDTO recvStageDTO();

    BeamDTO recvBeamDTO();

    //PlayersIniDTO recvPlayersIni();

    //PlayerDTO recvAPlayerDTO();

    //WormDTO recvWormIni();

    void sendCommandDTO(const CommandDTO& commandDto);

    SnapShot recvASnapShot();

    WormDTO recvAWormDTO();

    ~ClientProtocol() = default;

};


#endif //PROTOCOLO_CLIENT_PROTOCOL_H
