#ifndef WORMS_TALLER_1_SERVERPROTOCOL_H
#define WORMS_TALLER_1_SERVERPROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/DTO/LobbyAnswerDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"

#define ERROR 0

class ServerProtocol : public Protocol {

public:
    explicit ServerProtocol(Socket& skt);

    InitialStateDTO recvInitialStateDTO();

    ResponseInitialStateDTO recvReponseInitialStateDTO();

    void sendResolverInitialDTO(const ResolverInitialDTO& resolverInitial);

    void sendRoom(const RoomDTO &aRoomDTO);

    void sendMap(const MapDTO &aMap);

    void sendWorm(const WormDTO &aWorm);

    void sendBeam(const BeamDTO &aBeam);

    LobbyAnswerDTO recvLobbyAnswer();

    ~ServerProtocol();

};


#endif //WORMS_TALLER_1_SERVERPROTOCOL_H
