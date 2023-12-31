//
// Created by abraham on 08/11/23.
//

#include <iostream>
#include "GameParameters.h"
GameParameters::GameParameters() {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1/Server/GameParameters/" + "GameParameters.yaml");
    this->nodeInitial = YAML::LoadFile(fullPath);
    // basicamente el nodo inicial es como un diccionario le pasamos una clave y nos escupe un valor.
    parameters["FPS_GAME"] = 1/nodeInitial["FPS_GAME"].as<float>();

    parameters["MAX_WIDTH_PIXEL"] = nodeInitial["MAX_WIDTH_PIXEL"].as<float>();
    parameters["MAX_HEIGHT_PIXEL"] = nodeInitial["MAX_HEIGHT_PIXEL"].as<float>();

    parameters["VELOCITY_ITERATIONS"] = nodeInitial["VELOCITY_ITERATIONS"].as<float>();
    parameters["POSITION_ITERATIONS"] = nodeInitial["POSITION_ITERATIONS"].as<float>();
    parameters["GRAVITY"] = nodeInitial["GRAVITY"].as<float>();
    parameters["ANIMATION_ITERATION"] = nodeInitial["ANIMATION_ITERATION"].as<float>();
    parameters["POSITION_ADJUSTMENT"] = nodeInitial["POSITION_ADJUSTMENT"].as<float>();
    parameters["WORM_DRAG_SPEED"] = nodeInitial["WORM_DRAG_SPEED"].as<float>();
    parameters["WORM_INITIAL_HP"] = nodeInitial["WORM_INITIAL_HP"].as<float>();
    parameters["WORM_MAX_HP"] = nodeInitial["WORM_MAX_HP"].as<float>();
    parameters["WORM_BONUS_HP"] = nodeInitial["WORM_BONUS_HP"].as<float>();



    parameters["TIME_FOR_TURN"] = nodeInitial["TIME_FOR_TURN"].as<float>();
    parameters["TIME_EXTRA_AFTER_ATTACK"] = nodeInitial["TIME_EXTRA_AFTER_ATTACK"].as<float>();

    parameters["PROVISION_POSITION_Y_TO_INVOKE"] = nodeInitial["PROVISION_POSITION_Y_TO_INVOKE"].as<float>();
    parameters["PROVISION_HALF_HEIGHT"] = nodeInitial["PROVISION_HALF_HEIGHT"].as<float>();
    parameters["PROVISION_EXTRA_HP"] = nodeInitial["PROVISION_EXTRA_HP"].as<float>();
    parameters["PROVISION_EXTRA_MUNITION"] = nodeInitial["PROVISION_EXTRA_MUNITION"].as<float>();
    parameters["PROVISION_DAMAGE_EXPLOSION"] = nodeInitial["PROVISION_DAMAGE_EXPLOSION"].as<float>();
    parameters["PROVISION_IMPULSE_EXPLOSION_X"] = nodeInitial["PROVISION_IMPULSE_EXPLOSION_X"].as<float>();
    parameters["PROVISION_IMPULSE_EXPLOSION_Y"] = nodeInitial["PROVISION_IMPULSE_EXPLOSION_Y"].as<float>();



    parameters["WORM_DISTANCEX_FORWARD_JUMP"] = nodeInitial["WORM_DISTANCEX_FORWARD_JUMP"].as<float>();
    parameters["WORM_DISTANCEY_FORWARD_JUMP"] = nodeInitial["WORM_DISTANCEY_FORWARD_JUMP"].as<float>();

    parameters["WORM_DISTANCEX_BACK_JUMP"] = nodeInitial["WORM_DISTANCEX_BACK_JUMP"].as<float>();
    parameters["WORM_DISTANCEY_BACK_JUMP"] = nodeInitial["WORM_DISTANCEY_BACK_JUMP"].as<float>();

    parameters["WORM_HALF_HEIGHT"] = nodeInitial["WORM_HALF_HEIGHT"].as<float>();
    parameters["WORM_FRICTION"] = nodeInitial["WORM_FRICTION"].as<float>();
    parameters["WORM_FACTOR_IMPULSE_SCALING_DOWN"] = nodeInitial["WORM_FACTOR_IMPULSE_SCALING_DOWN"].as<float>();
    parameters["WORM_FACTOR_IMPULSE_CLIMBING_UP"] = nodeInitial["WORM_FACTOR_IMPULSE_CLIMBING_UP"].as<float>();
    parameters["WORM_MAX_FALL_DAMAGE"] = nodeInitial["WORM_MAX_FALL_DAMAGE"].as<float>();
    parameters["WORM_RESISTANCE_TO_HEIGHT"] = nodeInitial["WORM_RESISTANCE_TO_HEIGHT"].as<float>();

    // WORM_RESISTANCE_TO_HEIGHT

    // armas:
    parameters["WEAPON_MAX_MUNITION"] = nodeInitial["WEAPON_MAX_MUNITION"].as<float>();
    parameters["WEAPON_TIME_WAIT_DEFAULT"] = nodeInitial["WEAPON_TIME_WAIT_DEFAULT"].as<float>();
    parameters["WEAPON_ANGLE_INITIAL"] = nodeInitial["WEAPON_ANGLE_INITIAL"].as<float>();


    parameters["BAT_DAMAGE"] = nodeInitial["BAT_DAMAGE"].as<float>();
    parameters["BAT_IMPULSE_X"] = nodeInitial["BAT_IMPULSE_X"].as<float>();
    parameters["BAT_IMPULSE_Y"] = nodeInitial["BAT_IMPULSE_Y"].as<float>();
    parameters["BAT_MUNITION"] = nodeInitial["BAT_MUNITION"].as<float>();
    parameters["BAT_RAY_LENGTH"] = nodeInitial["BAT_RAY_LENGTH"].as<float>();
    parameters["BAT_ITERATIONS"] = nodeInitial["BAT_ITERATIONS"].as<float>();
    parameters["TELEPORT_DAMAGE"] = nodeInitial["TELEPORT_DAMAGE"].as<float>();
    parameters["TELEPORT_MUNITION"] = nodeInitial["TELEPORT_MUNITION"].as<float>();


    parameters["BAZOOKA_PROJECTILE_DAMAGE_MAX"] = nodeInitial["BAZOOKA_PROJECTILE_DAMAGE_MAX"].as<float>();
    parameters["BAZOOKA_IMPULSE_X_INITIAL"] = nodeInitial["BAZOOKA_IMPULSE_X_INITIAL"].as<float>();
    parameters["BAZOOKA_IMPULSE_Y_INITIAL"] = nodeInitial["BAZOOKA_IMPULSE_Y_INITIAL"].as<float>();

    parameters["BAZOOKA_MAX_IMPULSE_X"] = nodeInitial["BAZOOKA_MAX_IMPULSE_X"].as<float>();
    parameters["BAZOOKA_MAX_IMPULSE_Y"] = nodeInitial["BAZOOKA_MAX_IMPULSE_Y"].as<float>();
    parameters["INCREASE_IMPULSE_FOR_FPS"] = nodeInitial["INCREASE_IMPULSE_FOR_FPS"].as<float>();


    parameters["BAZOOKA_PROJECTILE_RADIO"] = nodeInitial["BAZOOKA_PROJECTILE_RADIO"].as<float>();
    parameters["BAZOOKA_PROJECTILE_MAX_IMPULSE_EXPLOSION"] =
        nodeInitial["BAZOOKA_PROJECTILE_MAX_IMPULSE_EXPLOSION"].as<float>();
    parameters["BAZOOKA_MUNITION"] = nodeInitial["BAZOOKA_MUNITION"].as<float>();
    parameters["BAZOOKA_RAY_LENGTH"] = nodeInitial["BAZOOKA_RAY_LENGTH"].as<float>();

    parameters["AIR_ATTACK_DAMAGE_MAIN_MISSILE"] = nodeInitial["AIR_ATTACK_DAMAGE_MAIN_MISSILE"].as<float>();
    parameters["AIR_ATTACK_MUNITION_INITIAL"] = nodeInitial["AIR_ATTACK_MUNITION_INITIAL"].as<float>();
    parameters["AIR_ATTACK_MISSILE_MAX_RADIO"] = nodeInitial["AIR_ATTACK_MISSILE_MAX_RADIO"].as<float>();
    parameters["AIR_ATTACK_MISSILE_IMPULSE_MAX"] = nodeInitial["AIR_ATTACK_MISSILE_IMPULSE_MAX"].as<float>();
    parameters["AIR_ATTACK_POSITION_Y_TO_INVOKE"] = nodeInitial["AIR_ATTACK_POSITION_Y_TO_INVOKE"].as<float>();


    parameters["DYNAMITE_DAMAGE_MAIN"] = nodeInitial["DYNAMITE_DAMAGE_MAIN"].as<float>();
    parameters["DYNAMITE_MUNITION_INITIAL"] = nodeInitial["DYNAMITE_MUNITION_INITIAL"].as<float>();
    parameters["DYNAMITE_MAX_RADIO"] = nodeInitial["DYNAMITE_MAX_RADIO"].as<float>();
    parameters["DYNAMITE_IMPULSE_MAX"] = nodeInitial["DYNAMITE_IMPULSE_MAX"].as<float>();
    parameters["DYNAMITE_OFFSET_X_TO_INVOKE"] = nodeInitial["DYNAMITE_OFFSET_X_TO_INVOKE"].as<float>();
    parameters["DYNAMITE_FRICTION"] = nodeInitial["DYNAMITE_FRICTION"].as<float>();

    // GRENADES:

    parameters["GRENADE_RAY_LENGTH"] = nodeInitial["GRENADE_RAY_LENGTH"].as<float>();
    parameters["GRENADE_IMPULSE_X_INITIAL"] = nodeInitial["GRENADE_IMPULSE_X_INITIAL"].as<float>();
    parameters["GRENADE_IMPULSE_Y_INITIAL"] = nodeInitial["GRENADE_IMPULSE_Y_INITIAL"].as<float>();
    parameters["GRENADE_MAX_IMPULSE_X"] = nodeInitial["GRENADE_MAX_IMPULSE_X"].as<float>();
    parameters["GRENADE_MAX_IMPULSE_Y"] = nodeInitial["GRENADE_MAX_IMPULSE_Y"].as<float>();


    parameters["GREEN_GRENADE_DAMAGE_MAIN"] = nodeInitial["GREEN_GRENADE_DAMAGE_MAIN"].as<float>();
    parameters["GREEN_GRENADE_MUNITION_INITIAL"] = nodeInitial["GREEN_GRENADE_MUNITION_INITIAL"].as<float>();
    parameters["GREEN_GRENADE_MAX_RADIO"] = nodeInitial["GREEN_GRENADE_MAX_RADIO"].as<float>();
    parameters["GREEN_GRENADE_MAX_IMPULSE"] = nodeInitial["GREEN_GRENADE_MAX_IMPULSE"].as<float>();

    parameters["HOLY_GRENADE_DAMAGE_MAIN"] = nodeInitial["HOLY_GRENADE_DAMAGE_MAIN"].as<float>();
    parameters["HOLY_GRENADE_MUNITION_INITIAL"] = nodeInitial["HOLY_GRENADE_MUNITION_INITIAL"].as<float>();
    parameters["HOLY_GRENADE_MAX_RADIO"] = nodeInitial["HOLY_GRENADE_MAX_RADIO"].as<float>();
    parameters["HOLY_GRENADE_MAX_IMPULSE"] = nodeInitial["HOLY_GRENADE_MAX_IMPULSE"].as<float>();


    parameters["BANANA_GRENADE_DAMAGE_MAIN"] = nodeInitial["BANANA_GRENADE_DAMAGE_MAIN"].as<float>();
    parameters["BANANA_GRENADE_MUNITION_INITIAL"] = nodeInitial["BANANA_GRENADE_MUNITION_INITIAL"].as<float>();
    parameters["BANANA_GRENADE_MAX_RADIO"] = nodeInitial["BANANA_GRENADE_MAX_RADIO"].as<float>();
    parameters["BANANA_GRENADE_MAX_IMPULSE"] = nodeInitial["BANANA_GRENADE_MAX_IMPULSE"].as<float>();
    parameters["BANANA_RESTITUION"] = nodeInitial["BANANA_RESTITUION"].as<float>();


    parameters["RED_GRENADE_DAMAGE_MAIN"] = nodeInitial["RED_GRENADE_DAMAGE_MAIN"].as<float>();
    parameters["RED_GRENADE_MUNITION_INITIAL"] = nodeInitial["RED_GRENADE_MUNITION_INITIAL"].as<float>();
    parameters["RED_GRENADE_MAX_RADIO"] = nodeInitial["RED_GRENADE_MAX_RADIO"].as<float>();
    parameters["RED_GRENADE_MAX_IMPULSE"] = nodeInitial["RED_GRENADE_MAX_IMPULSE"].as<float>();

    parameters["RED_GRENADE_FRAGMENT_DAMAGE_MAIN"] = nodeInitial["RED_GRENADE_FRAGMENT_DAMAGE_MAIN"].as<float>();
    parameters["RED_GRENADE_FRAGMENT_MAX_RADIO"] = nodeInitial["RED_GRENADE_FRAGMENT_MAX_RADIO"].as<float>();
    parameters["RED_GRENADE_FRAGMENT_MAX_IMPULSE"] = nodeInitial["RED_GRENADE_FRAGMENT_MAX_IMPULSE"].as<float>();



    parameters["MORTAR_DAMAGE_MAIN"] = nodeInitial["MORTAR_DAMAGE_MAIN"].as<float>();
    parameters["MORTAR_MUNITION_INITIAL"] = nodeInitial["MORTAR_MUNITION_INITIAL"].as<float>();
    parameters["MORTAR_MAX_RADIO"] = nodeInitial["MORTAR_MAX_RADIO"].as<float>();
    parameters["MORTAR_MAX_IMPULSE"] = nodeInitial["MORTAR_MAX_IMPULSE"].as<float>();
    parameters["MORTAR_RAY_LENGTH"] = nodeInitial["MORTAR_RAY_LENGTH"].as<float>();


    parameters["MORTAR_FRAGMENT_DAMAGE_MAIN"] = nodeInitial["MORTAR_FRAGMENT_DAMAGE_MAIN"].as<float>();
    parameters["MORTAR_FRAGMENT_MAX_RADIO"] = nodeInitial["MORTAR_FRAGMENT_MAX_RADIO"].as<float>();
    parameters["MORTAR_FRAGMENT_MAX_IMPULSE"] = nodeInitial["MORTAR_FRAGMENT_MAX_IMPULSE"].as<float>();


    parameters["FRAGMENT_LONG_DISTANCE"] = nodeInitial["FRAGMENT_LONG_DISTANCE"].as<float>();
    parameters["FRAGMENT_MIDDLE_DISTANCE"] = nodeInitial["FRAGMENT_MIDDLE_DISTANCE"].as<float>();
    parameters["FRAGMENT_SHORT_DISTANCE"] = nodeInitial["FRAGMENT_SHORT_DISTANCE"].as<float>();
}

float GameParameters::fragmentGetLongDist() const {
    return this->parameters.at("FRAGMENT_LONG_DISTANCE");
}

float GameParameters::fragmentGetMidDist() const {
    return this->parameters.at("FRAGMENT_MIDDLE_DISTANCE");
}

float GameParameters::fragmentGetShortDist() const {
    return this->parameters.at("FRAGMENT_SHORT_DISTANCE");
}


// --------------


float GameParameters::mortarGetMainDamage() const {
    return this->parameters.at("MORTAR_DAMAGE_MAIN");
}

float GameParameters::mortartGetMunitionInitial() const {
    return this->parameters.at("MORTAR_MUNITION_INITIAL");
}

float GameParameters::mortarGetMaxRadio() const {
    return this->parameters.at("MORTAR_MAX_RADIO");
}

float GameParameters::mortarGetMaxImpulse() const {
    return this->parameters.at("MORTAR_MAX_IMPULSE");
}

float GameParameters::mortarGetRayLength() const {
    return this->parameters.at("MORTAR_RAY_LENGTH");
}

float GameParameters::mortarFragmentGetMainDamage() const {
    return this->parameters.at("MORTAR_FRAGMENT_DAMAGE_MAIN");
}

float GameParameters::mortarFragmentGetMaxRadio() const {
    return this->parameters.at("MORTAR_FRAGMENT_MAX_RADIO");
}

float GameParameters::mortarFragmentGetMaxImpulse() const {
    return this->parameters.at("MORTAR_FRAGMENT_MAX_IMPULSE");
}


// -------------------

float GameParameters::redGrenadeGetMainDamage() const {
    return this->parameters.at("RED_GRENADE_DAMAGE_MAIN");
}

float GameParameters::redGrenadeGetMunitionInitial() const {
    return this->parameters.at("RED_GRENADE_MUNITION_INITIAL");
}

float GameParameters::redGrenadeGetMaxRadio() const {
    return this->parameters.at("RED_GRENADE_MAX_RADIO");
}

float GameParameters::redGrenadeGetMaxImpulse() const {
    return this->parameters.at("RED_GRENADE_MAX_IMPULSE");
}


float GameParameters::redGrenadeFragmentGetMainDamage() const {
    return this->parameters.at("RED_GRENADE_FRAGMENT_DAMAGE_MAIN");
}

float GameParameters::redGrenadeFragmentGetMaxRadio() const {
    return this->parameters.at("RED_GRENADE_FRAGMENT_MAX_RADIO");
}

float GameParameters::redGrenadeFragmentGetMaxImpulse() const {
    return this->parameters.at("RED_GRENADE_FRAGMENT_MAX_IMPULSE");
}



// -------------------
float GameParameters::bananaGetMainDamage() const {
    return this->parameters.at("BANANA_GRENADE_DAMAGE_MAIN");
}

float GameParameters::bananaGetMunitionInitial() const {
    return this->parameters.at("BANANA_GRENADE_MUNITION_INITIAL");
}

float GameParameters::bananaGetMaxRadio() const {
    return this->parameters.at("BANANA_GRENADE_MAX_RADIO");
}

float GameParameters::bananaGetMaxImpulse() const {
    return this->parameters.at("BANANA_GRENADE_MAX_IMPULSE");
}

float GameParameters::bananaGetRestitution() const {
    return this->parameters.at("BANANA_RESTITUION");
}

// ----------

float GameParameters::holyGrenadeGetMainDamage() const {
    return this->parameters.at("HOLY_GRENADE_DAMAGE_MAIN");
}

float GameParameters::holyGrenadeGetMunitionInitial() const {
    return this->parameters.at("HOLY_GRENADE_MUNITION_INITIAL");
}

float GameParameters::holyGrenadeGetMaxRadio() const {
    return this->parameters.at("HOLY_GRENADE_MAX_RADIO");
}

float GameParameters::holyGrenadeGetMaxImpulse() const {
    return this->parameters.at("HOLY_GRENADE_MAX_IMPULSE");
}


float GameParameters::grenadeGetRayLength() const {
    return this->parameters.at("GRENADE_RAY_LENGTH");
}

float GameParameters::grenadeGetImpulseXInitial() const {
    return this->parameters.at("GRENADE_IMPULSE_X_INITIAL");
}

float GameParameters::grenadeGetImpulseYInitial() const {
    return this->parameters.at("GRENADE_IMPULSE_Y_INITIAL");
}

float GameParameters::grenadeGetMaxImpulseX() const {
    return this->parameters.at("GRENADE_MAX_IMPULSE_X");
}

float GameParameters::grenadeGetMaxImpulseY() const {
    return this->parameters.at("GRENADE_MAX_IMPULSE_Y");
}

float GameParameters::greenGrenadeMainDamage() const {
    return this->parameters.at("GREEN_GRENADE_DAMAGE_MAIN");
}

float GameParameters::greenGrenadeMunitionInitial() const {
    return this->parameters.at("GREEN_GRENADE_MUNITION_INITIAL");
}

float GameParameters::greenGrenadeMaxRadio() const {
    return this->parameters.at("GREEN_GRENADE_MAX_RADIO");
}

float GameParameters::greenGrenadeMaxImpulse() const {
    return this->parameters.at("GREEN_GRENADE_MAX_IMPULSE");
}


// ----------

float GameParameters::dynamiteGetFriction() const {
    return this->parameters.at("DYNAMITE_FRICTION");
}

float GameParameters::dynamiteGetMainDamage() const {
    return this->parameters.at("DYNAMITE_DAMAGE_MAIN");
}

float GameParameters::dynamiteGetMunitionInitial() const {
    return this->parameters.at("DYNAMITE_MUNITION_INITIAL");
}

float GameParameters::dynamiteGetMaxRadio() const {
    return this->parameters.at("DYNAMITE_MAX_RADIO");
}

float GameParameters::dynamiteGetMaxImpulse() const {
    return this->parameters.at("DYNAMITE_IMPULSE_MAX");
}

float GameParameters::dynamiteGetOffsetXToInvoke() const {
    return this->parameters.at("DYNAMITE_OFFSET_X_TO_INVOKE");
}


float GameParameters::getWaitTimeWeaponDefault() const {
    return this->parameters.at("WEAPON_TIME_WAIT_DEFAULT");
}

float GameParameters::getMaxMunitionWeapon() const {
    return this->parameters.at("WEAPON_MAX_MUNITION");
}

float GameParameters::getMaxHPWorm() const {
    return this->parameters.at("WORM_MAX_HP");
}

int GameParameters::getAnimationIterations() const {
    return (int) this->parameters.at("ANIMATION_ITERATION");
}

float GameParameters::airAttackMissileGetDamage() const {
    return this->parameters.at("AIR_ATTACK_DAMAGE_MAIN_MISSILE");
}

float GameParameters::airAttackGetMunitionInitial() const {
    return this->parameters.at("AIR_ATTACK_MUNITION_INITIAL");
}

float GameParameters::airAttackMissleGetMaxRadio() const {
    return this->parameters.at("AIR_ATTACK_MISSILE_MAX_RADIO");
}

float GameParameters::airAttackMissileImpulseMax() const {
    return this->parameters.at("AIR_ATTACK_MISSILE_IMPULSE_MAX");
}

float GameParameters::airAttackGetPositionY() const {
    return this->parameters.at("AIR_ATTACK_POSITION_Y_TO_INVOKE");
}

float GameParameters::getProvisionHalfHeight() const {
    return this->parameters.at("PROVISION_HALF_HEIGHT");
}

float GameParameters::getProvisionExtraHP() const {
    return this->parameters.at("PROVISION_EXTRA_HP");
}

float GameParameters::getProvisionExtraMunition() const {
    return this->parameters.at("PROVISION_EXTRA_MUNITION");
}

float GameParameters::getProvisionDamageExplosion() const {
    return this->parameters.at("PROVISION_DAMAGE_EXPLOSION");
}

float GameParameters::getProvisionImpulseExplosionX() const {
    return this->parameters.at("PROVISION_IMPULSE_EXPLOSION_X");
}

float GameParameters::getProvisionImpulseExplosionY() const {
    return this->parameters.at("PROVISION_IMPULSE_EXPLOSION_Y");
}


float GameParameters::getPositionYForBoxes() const {
    return this->parameters.at("PROVISION_POSITION_Y_TO_INVOKE");
}

// WORM_RESISTANCE_TO_HEIGHT
float GameParameters::getWormMaxResistanceToHeight() const {
    return this->parameters.at("WORM_RESISTANCE_TO_HEIGHT");
}


float GameParameters::getMaxFallDamage() const {
    return this->parameters.at("WORM_MAX_FALL_DAMAGE");
}

float GameParameters::getBatIterations() const {
    return this->parameters.at("BAT_ITERATIONS");
}

float GameParameters::getFPS() const {
    return this->parameters.at("FPS_GAME");
}

int GameParameters::getTimeForTurn() const {
    return this->parameters.at("TIME_FOR_TURN");
}

int GameParameters::getTimeExtraAfterAttack() const {
    return this->parameters.at("TIME_EXTRA_AFTER_ATTACK");
}

int GameParameters::getVelocityIterations() const {
    return (int) parameters.at("VELOCITY_ITERATIONS");
}

int GameParameters::getPositionIterations() const {
    return (int) parameters.at("POSITION_ITERATIONS");
}

float GameParameters::getGravity() const {
    return parameters.at("GRAVITY");
}

YAML::Node GameParameters::getNodeInitial() {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1/Server/GameParameters/" + "GameParameters.yaml");
    YAML::Node nodeInitial = YAML::LoadFile(fullPath);
    return nodeInitial;
}

float GameParameters::getPositionAdjustmentStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["POSITION_ADJUSTMENT"].as<float>();
}

float GameParameters::getOffsetEdgeTop() {
    YAML::Node aNode = getNodeInitial();
    return aNode["OFFSET_EDGE_TOP"].as<float>();
}

float GameParameters::getOffsetWidth() {
    YAML::Node aNode = getNodeInitial();
    return aNode["OFFSET_EDGE_WIDTH"].as<float>();
}


float GameParameters::getBeamFrictionSlipperyStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["BEAM_SLIPPERY_FRICTION"].as<float>();
}

float GameParameters::getOffsetLateral() {
    YAML::Node aNode = getNodeInitial();
    return aNode["OFFSET_LATERAL"].as<float>();
}

float GameParameters::getOffsetSecondBarrier() {
    YAML::Node aNode = getNodeInitial();
    return aNode["OFFSET_Y_SECOND_BARRIER"].as<float>();
}

float GameParameters::getMaxHeightPixelStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["MAX_HEIGHT_PIXEL"].as<float>();
}

float GameParameters::getFPSStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["FPS_GAME"].as<float>();
}

float GameParameters::getOffsetWater() {
    YAML::Node aNode = getNodeInitial();
    return aNode["OFFSET_WATER"].as<float>();
}



float GameParameters::getMaxHeightPixel() const {
    return parameters.at("MAX_HEIGHT_PIXEL");
}

float GameParameters::getBeamMinimumScalableAngle() {
    YAML::Node aNode = getNodeInitial();
    return aNode["BEAM_MINIMUM_SCALABLE_ANGLE"].as<float>();
}

float GameParameters::getBeamMaximumUnscalableAngle() {
    YAML::Node aNode = getNodeInitial();
    return aNode["BEAM_MAXIMUM_UNSCALABLE_ANGLE"].as<float>();
}

float GameParameters::getBeamFriction() {
    YAML::Node aNode = getNodeInitial();
    return aNode["BEAM_FRICTION"].as<float>();
}



float GameParameters::getPositionAdjustment() const {
    return parameters.at("POSITION_ADJUSTMENT");
}

float GameParameters::getWormDragSpeed() const {
    return parameters.at("WORM_DRAG_SPEED");
}

float GameParameters::getWormHPBonus() const {
    return parameters.at("WORM_BONUS_HP");
}

float GameParameters::getInitialHPWorm() const {
    return parameters.at("WORM_INITIAL_HP");
}

float GameParameters::getDistXForwardJump() const {
    return parameters.at("WORM_DISTANCEX_FORWARD_JUMP");
}

float GameParameters::getDistYForwardJump() const {
    return parameters.at("WORM_DISTANCEY_FORWARD_JUMP");
}

float GameParameters::getDistXBackJump() const {
    return parameters.at("WORM_DISTANCEX_BACK_JUMP");
}

float GameParameters::getDistYBackJump() const {
    return parameters.at("WORM_DISTANCEY_BACK_JUMP");
}

float GameParameters::getHalfHeightWorm() const {
    return parameters.at("WORM_HALF_HEIGHT");
}

float GameParameters::getFrictionWorm() const {
    return parameters.at("WORM_FRICTION");
}

float GameParameters::getWeaponAngleInitial() const {
    return parameters.at("WEAPON_ANGLE_INITIAL");
}

float GameParameters::getBatDamage() const {
    return parameters.at("BAT_DAMAGE");
}

float GameParameters::getBatImpulseX() const {
    return parameters.at("BAT_IMPULSE_X");
}

float GameParameters::getBatImpulseY() const {
    return parameters.at("BAT_IMPULSE_Y");
}

float GameParameters::getBatMunition() const {
    return parameters.at("BAT_MUNITION");
}

float GameParameters::getBatRayLength() const {
    return parameters.at("BAT_RAY_LENGTH");
}

float GameParameters::getTeleportDamage() const {
    return parameters.at("TELEPORT_DAMAGE");
}

float GameParameters::getTeleportMunition() const {
    return parameters.at("TELEPORT_MUNITION");
}

float GameParameters::BazookaGetImpulseXInitial() const {
    return parameters.at("BAZOOKA_IMPULSE_X_INITIAL");
}

float GameParameters::getBazookaImpulseYInitial() const {
    return parameters.at("BAZOOKA_IMPULSE_Y_INITIAL");
}

float GameParameters::getBazookaMaxImpulseX() const {
    return parameters.at("BAZOOKA_MAX_IMPULSE_X");
}

float GameParameters::getBazookaMaxImpulseY() const {
    return parameters.at("BAZOOKA_MAX_IMPULSE_Y");
}

float GameParameters::getIncreaseImpulseForFPS() const {
    return parameters.at("INCREASE_IMPULSE_FOR_FPS");
}

float GameParameters::getBazookaProjectileDamageMax() const {
    return parameters.at("BAZOOKA_PROJECTILE_DAMAGE_MAX");
}

float GameParameters::getBazookProjectileRadio() const {
    return parameters.at("BAZOOKA_PROJECTILE_RADIO");
}

float GameParameters::getBazookaProjectilMaxImpulseExplosion() const {
    return parameters.at("BAZOOKA_PROJECTILE_MAX_IMPULSE_EXPLOSION");
}

float GameParameters::getBazookaMunition() const {
    return parameters.at("BAZOOKA_MUNITION");
}

float GameParameters::getBazookaRayLength() const {
    return parameters.at("BAZOOKA_RAY_LENGTH");
}

float GameParameters::getWormImpulseFactoScalingDown() const {
    return parameters.at("WORM_FACTOR_IMPULSE_SCALING_DOWN");
}

float GameParameters::getWormImpulseFactorClimbingUp() const {
    return parameters.at("WORM_FACTOR_IMPULSE_CLIMBING_UP");
}






