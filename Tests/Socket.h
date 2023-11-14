#ifndef MOCK_SOCKET_H
#define MOCK_SOCKET_H
#include <vector>

class Socket{
    private:
    std::vector<char> buffer;
    unsigned int send;
    unsigned int recv;

    public:
    Socket(){
        send = 0;
        recv = 0;
    }
    explicit Socket(int skt){
        send = 0;
        recv = 0;
    }
    Socket(const char* hostname, const char* servname){
        send = 0;
        recv = 0;
    }
    explicit Socket(const char* servname){
        send = 0;
        recv = 0;
    }
    int sendsome(const void* data, unsigned int sz, bool* was_closed){
        char* cdata = (char*) data;
        for (unsigned int i = 0;i<sz;i++){
            buffer.push_back(cdata[i]);
        }
        send = send+sz;
        return sz;
    }
    int recvsome(void* data, unsigned int sz, bool* was_closed){
        char* cdata = (char*) data;
        for (unsigned int i = 0;i<sz;i++){
            cdata[i] = buffer[recv];
            recv++;
        }
        return sz;
    }
    int sendall(const void* data, unsigned int sz, bool* was_closed){
        return sendsome(data,sz,was_closed);
    }
    int recvall(void* data, unsigned int sz, bool* was_closed){
        return recvsome(data,sz,was_closed);
    }
    std::vector<char> getBuffer(){
        return buffer;
    }
    void setBuffer(std::vector<char>& newBuffer){
        buffer = newBuffer;
    }
};
#endif