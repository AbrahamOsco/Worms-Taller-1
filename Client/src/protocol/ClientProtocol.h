#ifndef PROTOCOLO_CLIENT_PROTOCOL_H
#define PROTOCOLO_CLIENT_PROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/DTO/DTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"

class ClientProtocol : public Protocol {

public:
    explicit ClientProtocol(Socket& skt);

    MapDTO recvMap();

    void sendInitialStateDTO(const InitialStateDTO& initialStateDto);

    void sendResponseInitialStateDTO(const ResponseInitialStateDTO& responseInitial);

    ResolverInitialDTO recvResolverInitialDTO();

    RoomDTO recvRoom();

    BeamDTO recvBeam();

    WormDTO recvWorm();

    ~ClientProtocol();

};


#endif //PROTOCOLO_CLIENT_PROTOCOL_H
