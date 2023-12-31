#ifndef MOCK_SOCKET_H
#define MOCK_SOCKET_H
#define TEST_MODE_ON
#include <gmock/gmock.h>
#include <vector>

class Socket{
 private:
    std::vector<char> buffer;
    unsigned int send;
    unsigned int recv;

 public:
    // cppcheck-suppress uninitMemberVar
    Socket() {
        send = 0;
        recv = 0;
    }
    // cppcheck-suppress uninitMemberVar
    explicit Socket(int skt) {
        send = 0;
        recv = 0;
    }
    // cppcheck-suppress uninitMemberVar
    Socket(const char* hostname, const char* servname) {
        send = 0;
        recv = 0;
    }
    // cppcheck-suppress uninitMemberVar
    explicit Socket(const char* servname) {
        send = 0;
        recv = 0;
    }
    int sendsome(const void* data, unsigned int sz, bool* was_closed) {
        char* cdata = nullptr;
        cdata = (char*) data;
        if (cdata != nullptr) {
            for (unsigned int i = 0; i < sz; i++) {
                buffer.push_back(cdata[i]);
            }
            send = send+sz;
            return sz;
        } else {
            return 0;
        }
    }
    int recvsome(void* data, unsigned int sz, bool* was_closed) {
        char* cdata = nullptr;
        cdata = (char*) data;
        if (cdata != nullptr) {
            for (unsigned int i = 0; i < sz; i++) {
                cdata[i] = buffer[recv];
                recv++;
            }
            return sz;
        } else {
            return 0;
        }
    }
    int sendall(const void* data, unsigned int sz, bool* was_closed) {
        return sendsome(data, sz, was_closed);
    }
    int recvall(void* data, unsigned int sz, bool* was_closed) {
        return recvsome(data, sz, was_closed);
    }
    std::vector<char> getBuffer() {
        return buffer;
    }
    void setBuffer(const std::vector<char>& newBuffer) {
        buffer = newBuffer;
    }
};
#endif  // TESTS_MOCK_SOCKET_H_
