#ifndef WORMS_TALLER_1_PROTOCOL_H
#define WORMS_TALLER_1_PROTOCOL_H

#include "../Socket.h"

#include "MapDTO.h"
#include "BeamDTO.h"
#include "WormDTO.h"
#include <vector>
#include <stdexcept>
#include <netdb.h>


class Protocol {
protected:
    Socket& skt;
    bool wasClosed;

    void sendString(const std::string& aString);

    std::string recvString();

    void sendANumberByte(const unsigned int& aNumber);

    uint8_t recvANumberByte();

    void sendNum2Bytes(const unsigned int& aNumber);

    uint16_t recvNum2Bytes();

public:
    explicit Protocol(Socket& skt);

    bool isAvailable() const;

    virtual ~Protocol();
};


#endif //WORMS_TALLER_1_PROTOCOL_H
