#ifndef WORMS_TALLER_1_SERVERPROTOCOL_H
#define WORMS_TALLER_1_SERVERPROTOCOL_H

#include "../../Common/protocol/Protocol.h"
#include "../../Common/Socket.h"

class ServerProtocol : public Protocol {

public:
    explicit ServerProtocol(Socket& skt);

    void sendMap(MapDTO& aMap);

    void sendWorm(WormDTO& aWorm);

    void sendBeam(BeamDTO& aBeam);

    ~ServerProtocol();

};


#endif //WORMS_TALLER_1_SERVERPROTOCOL_H
