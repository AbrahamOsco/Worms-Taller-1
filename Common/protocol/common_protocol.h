#ifndef WORMS_TALLER_1_COMMON_PROTOCOL_H
#define WORMS_TALLER_1_COMMON_PROTOCOL_H

#include "common_socket.h"
#include "common_mapDTO.h"
#include "common_beamDTO.h"
#include "common_wormDTO.h"
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
    virtual ~Protocol();
};


#endif //WORMS_TALLER_1_COMMON_PROTOCOL_H
