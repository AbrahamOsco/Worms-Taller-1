//
// Created by abraham on 08/11/23.
//

#ifndef WORMS_TALLER_1_GAMEPARAMETERS_H
#define WORMS_TALLER_1_GAMEPARAMETERS_H

const float FPS_GAME = 1/60.0f;
const int VELOCITY_ITERATIONS = 6;  // cantida de iteraciones en la ecuaciones discretas de velocidad en el box2d
const int POSITION_TIERATIONS = 2;  // idem al de velocidad iteraciones.
const float GRAVEDAD = -10.0f; // apunta -10m/s hacia abajo. (por eso el menos).
const float POSITION_ADJUSTMENT = 60.0f; // Necesario para suavizar todas las animaciones

const float WORM_SPEED = 4.0f; // Velocidad del gusano no hay mucha logica
const float WORM_DRAG_SPEED = 0.2f; // velocidad de arrastre del gusano para caminar.

const float BONUS_HP = 25.0f;  // vida extra por si hay un jugador con menos gusanos entonces

#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <linux/limits.h>

class GameParameters {
private:
    std::map<std::string, float> parameters;
    YAML::Node nodeInitial;

public:

    GameParameters();

    float getFPS() const;

    int getVelocityIterations() const;

    int getPositionIterations() const;

    float getGravity() const;

    static float getPositionAdjustmentStatic();

    float getPositionAdjustment() const;

    float getWormDragSpped() const;

    float getInitialHPWorm() const;

    float getWormHPBonus() const;

    float getDistXForwardJump() const;

    float getDistYForwardJump() const;

    float getDistXBackJump() const;

    float getDistYBackJump() const;

    float getHalfHeightWorm() const;

    float getFrictionWorm() const;

    ~GameParameters() = default;
};


#endif //WORMS_TALLER_1_GAMEPARAMETERS_H
