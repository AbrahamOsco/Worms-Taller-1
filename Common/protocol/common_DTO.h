#ifndef PROTOCOLO_COMMON_DTO_H
#define PROTOCOLO_COMMON_DTO_H

enum OpType {
    MAP = 0,
    WORM = 1,
    BEAM = 2,
};

class DTO {
protected:
    OpType opType;
public:


    explicit DTO(OpType opType) : opType(opType) {}
    OpType getOpType() { return opType;}
    virtual ~DTO()= default;
};


#endif //PROTOCOLO_COMMON_DTO_H
