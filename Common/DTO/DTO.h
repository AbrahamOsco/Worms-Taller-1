#ifndef PROTOCOLO_COMMON_DTO_H
#define PROTOCOLO_COMMON_DTO_H

enum OperationType {
    INITIAL_STATE = 250,
    MAP = 1,
    WORM = 2,
    BEAM = 3,
    CREATE_GAME = 10,
    JOIN_GAME = 11
};

class DTO {
protected:
    OperationType opType;
public:
    explicit DTO(OperationType opType);

    OperationType getOperationType() const;

    void setOperationType(const OperationType& anOpType);

    virtual ~DTO() = default;
};



#endif //PROTOCOLO_COMMON_DTO_H
