#ifndef PROTOCOLO_COMMON_DTO_H
#define PROTOCOLO_COMMON_DTO_H

enum OperationType {
    INITIAL_STATE = 250,  // Si imprime 250 es porque no esta inicializado.
    MAP = 1,
    WORM = 2,
    BEAM = 3,
    CREATE_GAME = 10,
    JOIN_GAME = 11,
    SCENARIO_LIST_REQUEST = 20,
    RESPONSE_INITIAL_CREATE_GAME = 21,
    FINAL_CREATE_GAME = 22,
    RESPONSE_FINAL_CREATE_GAME = 23,
    RESPONSE_FINAL_JOIN_GAME = 24,
    ROOM_LIST_REQUEST = 25,
    RESPONSE_INITIAL_JOIN_GAME = 26,
    FINAL_JOIN_GAME = 27,
    ROOM_GAME = 28
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
