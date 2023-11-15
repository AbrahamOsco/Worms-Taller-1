//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_WORM_H
#define WORMS_TALLER_1_WORM_H


#include "../GameObject.h"
#include "../../loaderParams/LoaderParams.h"
#include "../../animation/Animation.h"
#include <cmath>

class Worm : public GameObject {
private:
    size_t m_hpWorm;
    Direction m_directionLook;
    MoveWorm m_moveWorm;
    TypeFocusWorm m_typeFocus;
    TypeWeapon m_weaponCurrent;

    int m_xCrosshair;
    int m_yCrosshair;
    TypeSight m_typeSight;

    Animation m_animation;

public:
    explicit Worm(int x, int y, const size_t &hpWorm, const Direction &direction,
                  const TypeFocusWorm &focus, const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrosshair, int yCrosshair, const TypeSight &typeSight);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override;

    void animationState();

    int calcularAngulo(int x, int y, int xCrosshair, int yCrosshair, const Direction &direction);
};


#endif //WORMS_TALLER_1_WORM_H
