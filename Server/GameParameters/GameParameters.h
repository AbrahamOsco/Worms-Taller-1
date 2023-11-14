//
// Created by abraham on 08/11/23.
//

#ifndef WORMS_TALLER_1_GAMEPARAMETERS_H
#define WORMS_TALLER_1_GAMEPARAMETERS_H

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

    static YAML::Node getNodeInitial();

    static float getPositionAdjustmentStatic();

    static float getBeamMinimumScalableAngle();

    static float getBeamMaximumUnscalableAngle();

    static float getMaxHeightPixelStatic();

    float getMaxHeightPixel() const;

    static float getBeamFriction();

    float getPositionAdjustment() const;

    float getWormDragSpeed() const;

    float getInitialHPWorm() const;

    float getWormHPBonus() const;

    float getDistXForwardJump() const;

    float getDistYForwardJump() const;

    float getDistXBackJump() const;

    float getDistYBackJump() const;

    float getHalfHeightWorm() const;

    float getFrictionWorm() const;

    float getWormImpulseFactoScalingDown() const;

    float getWormImpulseFactorClimbingUp() const;

    float getWeaponAngleInitial() const;

    float getBatDamage() const;

    float getBatImpulseX() const;

    float getBatImpulseY() const;

    float getBatMunition() const;

    float getBatRayLength() const;

    float getTeleportDamage() const;

    float getTeleportMunition() const;

    float getBazookaImpulseXInitial() const;

    float getBazookaImpulseYInitial() const;

    float getBazookaProjectileDamageMax() const;

    float getBazookProjectileRadio() const;

    float getBazookaProjectilMaxImpulseExplosion() const;

    float getBazookaMuntion() const;

    float getBazookaRayLength() const;

    ~GameParameters() = default;
};


#endif //WORMS_TALLER_1_GAMEPARAMETERS_H
