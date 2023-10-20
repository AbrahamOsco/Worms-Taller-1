#ifndef WORMS_TALLER_1_SERVER_PROTOCOL_H
#define WORMS_TALLER_1_SERVER_PROTOCOL_H

#include "common_protocol.h"

class ServerProtocol : public Protocol {

public:
    explicit ServerProtocol(Socket& skt);

    void sendMap(MapDTO& aMap);
    void sendWorm(WormDTO& aWorm);
    void sendBeam(BeamDTO& aBeam);
    ~ServerProtocol();
};


#endif //WORMS_TALLER_1_SERVER_PROTOCOL_H
