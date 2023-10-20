#ifndef PROTOCOLO_COMMON_DTO_H
#define PROTOCOLO_COMMON_DTO_H


class DTO {
public:
    enum OpType {
        MAP = 0,
        WORM = 1,
        BEAM = 2,
    };

    DTO()= default;
    virtual int getOpType(){ return -1;}
    ~DTO()= default;
};


#endif //PROTOCOLO_COMMON_DTO_H
