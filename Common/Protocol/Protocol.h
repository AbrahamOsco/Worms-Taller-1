#ifndef WORMS_TALLER_1_PROTOCOL_H
#define WORMS_TALLER_1_PROTOCOL_H

#ifdef TEST_MODE_ON
#include "../../Tests/Mock_Socket.h"
#else
#include "../Socket/Socket.h"
#endif

#include "../DTO/WormDTO.h"
#include <vector>
#include <stdexcept>
#include <netdb.h>
#define CLOSED_CONNECTION 0

class Protocol {

protected:
    Socket& skt;
    bool wasClosed;

    void sendString(const std::string& aString);

    std::string recvString();

public:
    explicit Protocol(Socket& skt);

    void sendANumberByte(const unsigned int& aNumber);

    uint8_t recvANumberByte();

    void sendNum2Bytes(const unsigned int& aNumber);

    uint16_t recvNum2Bytes();

    bool isAvailable() const;

    virtual ~Protocol();
};


#endif //WORMS_TALLER_1_PROTOCOL_H
