#ifndef SUPER_SOCKET_H
#define SUPER_SOCKET_H

class SuperSocket{
    public:
    virtual int sendsome(const void* data, unsigned int sz, bool* was_closed) = 0;
    virtual int recvsome(void* data, unsigned int sz, bool* was_closed) = 0;
    virtual int sendall(const void* data, unsigned int sz, bool* was_closed) = 0;
    virtual int recvall(void* data, unsigned int sz, bool* was_closed) = 0;
};
#endif
