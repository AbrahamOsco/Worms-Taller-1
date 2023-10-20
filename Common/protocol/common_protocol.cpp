#include "common_protocol.h"

Protocol::Protocol(Socket& skt) : skt(skt), wasClosed(false) {}

void Protocol::sendString(const std::string& aString) {
    size_t s = 0;
    sendNum2Bytes(aString.size());
    s += skt.sendall(aString.data(), aString.size(), &wasClosed);
    if (s != aString.size()) {
        throw std::runtime_error("Error al enviar la cadena: " + aString + "\n");
    }
}


std::string Protocol::recvString() {
    size_t s = 0;
    size_t tamanioBuffer = recvNum2Bytes();
    std::vector<char> buffer(tamanioBuffer);
    s += skt.recvall(buffer.data(), tamanioBuffer, &wasClosed);
    if (s != tamanioBuffer) {
        throw std::runtime_error("Error al recibir la cadena\n");
    }
    return std::string(buffer.begin(), buffer.end());
}

void Protocol::sendANumberByte(const unsigned int& aNumber) {
    uint8_t operacion = aNumber;
    size_t s = 0;
    s += skt.sendall(&operacion, sizeof(operacion), &wasClosed);
    if (s != sizeof(operacion)) {
        throw std::runtime_error("Error al enviar la operacion Numerica\n");
    }
}


uint8_t Protocol::recvANumberByte() {
    uint8_t operacion;
    size_t s = 0;
    s += skt.recvall(&operacion, sizeof(operacion), &wasClosed);
    if (s != sizeof(operacion)) {
        //return CIERRA_CONEXION; ????
    }
    return operacion;
}


void Protocol::sendNum2Bytes(const unsigned int& aNumber) {
    uint16_t sendNumber = aNumber;
    sendNumber = htons(sendNumber);
    size_t s = 0;
    s += skt.sendall(&sendNumber, sizeof(sendNumber), &wasClosed);
    if (s != sizeof(sendNumber)) {
        throw std::runtime_error("Error al enviar la operacion Numerica\n");
    }
}


uint16_t Protocol::recvNum2Bytes() {
    uint16_t unNumero;
    size_t s = 0;
    s += skt.recvall(&unNumero, sizeof(unNumero), &wasClosed);
    if (s != sizeof(unNumero)) {
        throw std::runtime_error("Error al recibir 2 Bytes\n");
    }
    unNumero = ntohs(unNumero);
    return unNumero;
}

Protocol::~Protocol() {}
