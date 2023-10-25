#ifndef WORMS_TALLER_1_SERVERPROTOCOL_H
#define WORMS_TALLER_1_SERVERPROTOCOL_H

#include "../../../Common/Protocol/Protocol.h"
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/DTO/LobbyAnswerDTO.h"

class ServerProtocol : public Protocol {

public:
    explicit ServerProtocol(Socket& skt);

    void sendMap(const MapDTO &aMap);

    void sendWorm(const WormDTO &aWorm);

    void sendBeam(const BeamDTO &aBeam);

    LobbyAnswerDTO recvLobbyAnswer();

    ~ServerProtocol();

};


#endif //WORMS_TALLER_1_SERVERPROTOCOL_H
