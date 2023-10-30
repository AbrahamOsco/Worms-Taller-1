#ifndef PROTOCOLO_CLIENT_PROTOCOL_H
#define PROTOCOLO_CLIENT_PROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/DTO/DTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/DTO/StageDTO.h"

class ClientProtocol : public Protocol {

public:
    explicit ClientProtocol(Socket& skt);

    void sendInitialStateDTO(const InitialStateDTO& initialStateDto);

    void sendResponseInitialStateDTO(const ResponseInitialStateDTO& responseInitial);

    ResolverInitialDTO recvResolverInitialDTO();

    RoomDTO recvRoom();

    StageDTO recvStageDTO();

    BeamDTO recvBeamDTO();

    WormDTO recvWorm();


    ~ClientProtocol();

};


#endif //PROTOCOLO_CLIENT_PROTOCOL_H
