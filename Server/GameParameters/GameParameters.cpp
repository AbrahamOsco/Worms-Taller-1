//
// Created by abraham on 08/11/23.
//

#include <iostream>
#include "GameParameters.h"
GameParameters::GameParameters() {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1/Server/GameParameters/" + "GameParameters.yaml" );
    this->nodeInitial = YAML::LoadFile(fullPath); //basicamente el nodo inicial es como un diccionario le pasamos una clave y nos escupe un valor.
    parameters["FPS_GAME"] = 1/nodeInitial["FPS_GAME"].as<float>();

    parameters["MAX_WIDTH_PIXEL"] = nodeInitial["MAX_WIDTH_PIXEL"].as<float>();
    parameters["MAX_HEIGHT_PIXEL"] = nodeInitial["MAX_HEIGHT_PIXEL"].as<float>();

    parameters["VELOCITY_ITERATIONS"] = nodeInitial["VELOCITY_ITERATIONS"].as<float>();
    parameters["POSITION_ITERATIONS"] = nodeInitial["POSITION_ITERATIONS"].as<float>();
    parameters["GRAVITY"] = nodeInitial["GRAVITY"].as<float>();
    parameters["POSITION_ADJUSTMENT"] = nodeInitial["POSITION_ADJUSTMENT"].as<float>();
    parameters["WORM_DRAG_SPEED"] = nodeInitial["WORM_DRAG_SPEED"].as<float>();
    parameters["WORM_INITIAL_HP"] = nodeInitial["WORM_INITIAL_HP"].as<float>();
    parameters["WORM_BONUS_HP"] = nodeInitial["WORM_BONUS_HP"].as<float>();

    parameters["WORM_DISTANCEX_FORWARD_JUMP"] = nodeInitial["WORM_DISTANCEX_FORWARD_JUMP"].as<float>();
    parameters["WORM_DISTANCEY_FORWARD_JUMP"] = nodeInitial["WORM_DISTANCEY_FORWARD_JUMP"].as<float>();

    parameters["WORM_DISTANCEX_BACK_JUMP"] = nodeInitial["WORM_DISTANCEX_BACK_JUMP"].as<float>();
    parameters["WORM_DISTANCEY_BACK_JUMP"] = nodeInitial["WORM_DISTANCEY_BACK_JUMP"].as<float>();

    parameters["WORM_HALF_HEIGHT"] = nodeInitial["WORM_HALF_HEIGHT"].as<float>();
    parameters["WORM_FRICTION"] = nodeInitial["WORM_FRICTION"].as<float>();
    parameters["WORM_FACTOR_IMPULSE_SCALING_DOWN"] = nodeInitial["WORM_FACTOR_IMPULSE_SCALING_DOWN"].as<float>();
    parameters["WORM_FACTOR_IMPULSE_CLIMBING_UP"] = nodeInitial["WORM_FACTOR_IMPULSE_CLIMBING_UP"].as<float>();


    // armas:
    parameters["WEAPON_ANGLE_INITIAL"] = nodeInitial["WEAPON_ANGLE_INITIAL"].as<float>();

    parameters["BAT_DAMAGE"] = nodeInitial["BAT_DAMAGE"].as<float>();
    parameters["BAT_IMPULSE_X"] = nodeInitial["BAT_IMPULSE_X"].as<float>();
    parameters["BAT_IMPULSE_Y"] = nodeInitial["BAT_IMPULSE_Y"].as<float>();
    parameters["BAT_MUNITION"] = nodeInitial["BAT_MUNITION"].as<float>();
    parameters["BAY_RAY_LENGTH"] = nodeInitial["BAY_RAY_LENGTH"].as<float>();

    parameters["TELEPORT_DAMAGE"] = nodeInitial["TELEPORT_DAMAGE"].as<float>();
    parameters["TELEPORT_MUNITION"] = nodeInitial["TELEPORT_MUNITION"].as<float>();


    parameters["BAZOOKA_PROJECTILE_DAMAGE_MAX"] = nodeInitial["BAZOOKA_PROJECTILE_DAMAGE_MAX"].as<float>();
    parameters["BAZOOKA_IMPULSE_X_INITIAL"] = nodeInitial["BAZOOKA_IMPULSE_X_INITIAL"].as<float>();
    parameters["BAZOOKA_IMPULSE_Y_INITIAL"] = nodeInitial["BAZOOKA_IMPULSE_Y_INITIAL"].as<float>();

    parameters["BAZOOKA_MAX_IMPULSE_X"] = nodeInitial["BAZOOKA_MAX_IMPULSE_X"].as<float>();
    parameters["BAZOOKA_MAX_IMPULSE_Y"] = nodeInitial["BAZOOKA_MAX_IMPULSE_Y"].as<float>();
    parameters["INCREASE_IMPULSE_FOR_FPS"] = nodeInitial["INCREASE_IMPULSE_FOR_FPS"].as<float>();


    parameters["BAZOOKA_PROJECTILE_RADIO"] = nodeInitial["BAZOOKA_PROJECTILE_RADIO"].as<float>();
    parameters["BAZOOKA_PROJECTILE_MAX_IMPULSE_EXPLOSION"] = nodeInitial["BAZOOKA_PROJECTILE_MAX_IMPULSE_EXPLOSION"].as<float>();
    parameters["BAZOOKA_MUNITION"] = nodeInitial["BAZOOKA_MUNITION"].as<float>();
    parameters["BAZOOKA_RAY_LENGTH"] = nodeInitial["BAZOOKA_RAY_LENGTH"].as<float>();
}



float GameParameters::getFPS() const{
    return this->parameters.at("FPS_GAME");
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
    std::string fullPath(startPath + "/Worms-Taller-1/Server/GameParameters/" + "GameParameters.yaml" );
    YAML::Node nodeInitial = YAML::LoadFile(fullPath);
    return nodeInitial;
}

float GameParameters::getPositionAdjustmentStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["POSITION_ADJUSTMENT"].as<float>();
}

float GameParameters::getMaxHeightPixelStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["MAX_HEIGHT_PIXEL"].as<float>();
}

float GameParameters::getFPSStatic() {
    YAML::Node aNode = getNodeInitial();
    return aNode["FPS_GAME"].as<float>();
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
    return parameters.at("BAY_RAY_LENGTH");
}

float GameParameters::getTeleportDamage() const {
    return parameters.at("TELEPORT_DAMAGE");
}

float GameParameters::getTeleportMunition() const {
    return parameters.at("TELEPORT_MUNITION");
}

float GameParameters::getBazookaImpulseXInitial() const {
    return parameters.at("BAZOOKA_IMPULSE_X_INITIAL");
}

float GameParameters::getBazookaImpulseYInitial() const {
    return parameters.at("BAZOOKA_IMPULSE_Y_INITIAL");
}

float GameParameters::getBazookaMaxImpulseX() const{
    return parameters.at("BAZOOKA_MAX_IMPULSE_X");
}

float GameParameters::getBazookaMaxImpulseY() const{
    return parameters.at("BAZOOKA_MAX_IMPULSE_Y");
}

float GameParameters::getIncreaseImpulseForFPS() const{
    return parameters.at("INCREASE_IMPULSE_FOR_FPS");
}

float GameParameters::getBazookaProjectileDamageMax() const {
    try{
        return parameters.at("BAZOOKA_PROJECTILE_DAMAGE_MAX");
    } catch (std::exception& e ){
        std::cerr << e.what() << "\n";
        return 50.0f;
    }
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




