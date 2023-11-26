//
// Created by riclui on 16/11/23.
//

#ifndef WORMS_TALLER_1_CAMERA_H
#define WORMS_TALLER_1_CAMERA_H

#include "SDL2pp/SDL2pp.hh"
#include "../inputs/Input.h"
#include "../../../Common/Queue/Queue.h"
#include "../command/Command.h"

const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1080;


class Camera {
private:
    SDL2pp::Point m_target;
    SDL2pp::Point m_position;
    SDL2pp::Rect  m_viewBox;

public:
    Camera();
    void update();
    SDL2pp::Rect getViewBox();
    SDL2pp::Point getPosition();
    void setTarget(SDL2pp::Point &target);
    void handleMouseMovement(Input & input);
};


#endif //WORMS_TALLER_1_CAMERA_H
