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

    static float getFPSStatic();

    int getVelocityIterations() const;

    int getPositionIterations() const;

    float getGravity() const;

    static YAML::Node getNodeInitial();

    static float getPositionAdjustmentStatic();

    static float getBeamMinimumScalableAngle();

    static float getBeamMaximumUnscalableAngle();

    static float getMaxHeightPixelStatic();

    static float getBeamFrictionSlipperyStatic();

    static float getOffsetEdgeTop();

    static float getOffsetWidth();

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

    float getBazookaMunition() const;

    float getBazookaRayLength() const;

    ~GameParameters() = default;

    float getBazookaMaxImpulseX() const;

    float getBazookaMaxImpulseY() const;

    float getIncreaseImpulseForFPS() const;

    float getBatIterations() const;

    float getMaxFallDamage() const;

    float getWormMaxResistanceToHeight() const;

    int getTimeForTurn() const;

    int getTimeExtraAfterAttack() const;

    float getPositionYForBoxes() const;

    float getProvisionHalfHeight() const;

    float getProvisionExtraHP() const;

    float getProvisionExtraMunition() const;

    float getProvisionDamageExplosion() const;

    float getProvisionImpulseExplosionX() const;

    float getProvisionImpulseExplosionY() const;

    int getMaxValueWind() const;

    float airAttackGetPositionY() const;

    float airAttackMissileGetDamage() const;

    float airAttackGetMunitionInitial() const;

    float airAttackMissleGetMaxRadio() const;

    float airAttackMissileImpulseMax() const;

};


#endif //WORMS_TALLER_1_GAMEPARAMETERS_H
