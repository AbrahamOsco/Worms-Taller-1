#ifndef PROTOCOLO_CLIENT_PROTOCOL_H
#define PROTOCOLO_CLIENT_PROTOCOL_H

#include "../../Common/Protocol/Protocol.h"

class ClientProtocol : public Protocol {

public:
    explicit ClientProtocol(Socket& skt);

    MapDTO recvMap();
    BeamDTO recvBeam();
    WormDTO recvWorm();
    ~ClientProtocol();
};


#endif //PROTOCOLO_CLIENT_PROTOCOL_H
