#ifndef PROTOCOLO_COMMON_WORMDTO_H
#define PROTOCOLO_COMMON_WORMDTO_H

#include <cstddef>
#include "DTO.h"

enum Direction{
    RIGHT = 1, LEFT = 2
};
enum TypeFocusWorm{
    FOCUS = 1, NO_FOCUS = 2
};
enum MoveWorm{
    STANDING = 1, WALKING = 2, JUMPING =3
};

class WormDTO : public DTO {
private:
    size_t positionX;
    size_t positionY;
    size_t hpWorm;
    Direction directionLook;
    MoveWorm moveWorm;
    TypeFocusWorm typeFocus;

public:
    WormDTO();

    WormDTO(const size_t& positionX, const size_t& positionY, const size_t& hpWorm, const Direction& aDirection, const TypeFocusWorm& aTypeFocus, const MoveWorm& aMoveWorm);

    size_t getIdWorm() const;

    size_t getPositionX() const;

    size_t getPositionY() const;

    size_t getHpWorm() const;

    Direction getDirectionLook() const;

    TypeFocusWorm getTypeFocus() const;

    MoveWorm getMoveWorm() const;

    void setPositionX(const size_t &positionX);

    void setPositionY(const size_t &positionY);

    void setHpWorm(const size_t &hpWorm);

    void setDirectionLook(const Direction &directionLook);

    void setTypeFocus(const TypeFocusWorm &typeFocus);

    void setMoveWorm(const MoveWorm &moveWorm);

    ~WormDTO() = default;

};


#endif //PROTOCOLO_COMMON_WORMDTO_H
