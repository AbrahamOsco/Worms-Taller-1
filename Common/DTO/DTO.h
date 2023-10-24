#ifndef PROTOCOLO_COMMON_DTO_H
#define PROTOCOLO_COMMON_DTO_H

enum OpType {
    INITIAL_STATE = 250,
    MAP = 1,
    WORM = 2,
    BEAM = 3,
    CREATE_GAME = 10,
    JOIN_GAME = 11
};

class DTO {
protected:
    OpType opType;
public:
    explicit DTO(OpType opType);

    OpType getOperationType() const;

    void setOperationType(const OpType& anOpType);

    virtual ~DTO() = default;
};



#endif //PROTOCOLO_COMMON_DTO_H
