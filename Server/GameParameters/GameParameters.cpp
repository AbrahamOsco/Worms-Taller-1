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
    std::cout << "FUll path es " << fullPath << "\n";
    this->nodeInitial = YAML::LoadFile(fullPath); //basicamente el nodo inicial es como un diccionario le pasamos una clave y nos escupe un valor.
    parameters["FPS_GAME"] = 1/nodeInitial["FPS_GAME"].as<float>();
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

float GameParameters::getPositionAdjustmentStatic() {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1/Server/GameParameters/" + "GameParameters.yaml" );
    std::cout << "FUll path es " << fullPath << "\n";
    YAML::Node nodeInitial = YAML::LoadFile(fullPath);

    return nodeInitial["POSITION_ADJUSTMENT"].as<float>();
}

float GameParameters::getPositionAdjustment() const {
    return parameters.at("POSITION_ADJUSTMENT");
}

float GameParameters::getWormDragSpped() const {
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


