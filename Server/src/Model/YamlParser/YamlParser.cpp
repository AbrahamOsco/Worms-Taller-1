//
// Created by abraham on 30/10/23.
//

#include <iostream>
#include "YamlParser.h"

YamlParser::YamlParser() {
}

void YamlParser::loadDataStage(const std::string &aStageName, float &height, float &length, std::vector<Beam> &aBeams,
                               std::map<size_t, std::pair<float, float>> &idPosWorms, std::string &background) {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string stgNamNoSpace = aStageName;
    stgNamNoSpace.erase(std::remove(stgNamNoSpace.begin(), stgNamNoSpace.end(), ' '), stgNamNoSpace.end());
    std::string fullPath(startPath + "/Worms-Taller-1" + "/Stages/"+ stgNamNoSpace + ".yaml");
    YAML::Node node = YAML::LoadFile(fullPath);
    std::map<size_t, std::pair<float, float>> idPosInitialWorms;
    YAML::Node wormsNode = node["worms"];
    size_t idWorm = 0;
    for (const auto& posWorm : node["worms"]) {
        float posInitialX = posWorm["positionX"].as<float>();
        float posInitialY = posWorm["positionY"].as<float>();
        idPosInitialWorms[idWorm] = std::pair<float, float>{posInitialX, posInitialY};
        idWorm++;
    }
    height = node["height"].as<float>();
    length = node["width"].as<float>();
    aBeams = getBeams(node["beams"]);
    background = node["background"].as<std::string>();
    idPosWorms = idPosInitialWorms;
}

std::vector<Beam> YamlParser::getBeams(const YAML::Node &beamsNode) {
    std::vector<Beam> beams;
    for (YAML::const_iterator it = beamsNode.begin(); it != beamsNode.end(); ++it) {
        const YAML::Node& beamNode = *it;
        float length = beamNode["length"].as<float>();
        float angle = beamNode["angle"].as<float>();
        float xCenter = beamNode["x"].as<float>();
        float yCenter = beamNode["y"].as<float>();
        float height = 0.4;
        TypeBeam typeBeam;
        if (length == 3.0) {
            typeBeam = TypeBeam::SHORT_BEAM;
        } else if (length == 6.0) {
            typeBeam = TypeBeam::LONG_BEAM;
        } else if (length == 1500.0) {
            typeBeam = TypeBeam::WATER_BEAM;
        }
        Beam beam(typeBeam, xCenter, yCenter, length, height, angle);
        beams.push_back(beam);
    }
    return beams;
}

size_t YamlParser::getNumberWorms(const std::string &aStageName) {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string stgNamNoSpace = aStageName;
    stgNamNoSpace.erase(std::remove(stgNamNoSpace.begin(), stgNamNoSpace.end(), ' '), stgNamNoSpace.end());
    std::string fullPath(startPath + "/Worms-Taller-1" + "/Stages/"+ stgNamNoSpace + ".yaml");
    YAML::Node node = YAML::LoadFile(fullPath);
    YAML::Node wormsNode = node["worms"];
    size_t numberWorms = 0;
    for (const auto& posWorm : node["worms"]) {
        numberWorms++;
    }
    return numberWorms;
}


void YamlParser::getScenarioAndMaxWorms(std::vector<std::string>& vecScenarios,
        std::vector<size_t>& vecMaxNumberWorms) {
    std::vector<std::string> scenarioNames;

    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1" + "/Stages/"+ "StageNames" + ".yaml");
    std::vector<size_t> maxNumberWorms;
    try {
        YAML::Node config = YAML::LoadFile(fullPath);
        for (const auto& scenario : config["namesScenarios"]) {
            auto name = scenario["name"].as<std::string>();
            scenarioNames.push_back(name);
            maxNumberWorms.push_back(getNumberWorms(name));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    vecScenarios = scenarioNames;
    vecMaxNumberWorms = maxNumberWorms;
}



