//
// Created by riclui on 06/11/23.
//

#ifndef WORMS_TALLER_1_COMMANDDTO_H
#define WORMS_TALLER_1_COMMANDDTO_H


#include <cstddef>
#include "DTO.h"

enum TypeCommand {
    LEFT_CMD,
    RIGHT_CMD,
    UP_CMD,
    DOWN_CMD,
    JUMP_BACK_CMD,
    JUMP_FORWARD_CMD,
    SELECT_BAZOOKA,
    SELECT_MORTAR,
    SELECT_RED_GRENADE,
    SELECT_GREEN_GRENADE,
    SELECT_BANANA,
    SELECT_HOLY_GRENADE,
    SELECT_DYNAMITE,
    SELECT_BAT,
    SELECT_AIR_ATTACK,
    SELECT_TELEPORT,
    CHARGE_CMD,
    FIRE_CMD, // comando 17
    TELEPORT_MOVE,
    CLOSE_GAME,
    NONE
};

class CommandDTO : public DTO {
private:
    TypeCommand m_typeCommand;
    int m_x;
    int m_y;
public:
    CommandDTO();
    void setTypeCommand(const TypeCommand& typeCommand);
    TypeCommand getTypeCommand() const;
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
};


#endif //WORMS_TALLER_1_COMMANDDTO_H
