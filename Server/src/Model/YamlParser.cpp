//
// Created by abraham on 30/10/23.
//

#include <iostream>
#include "YamlParser.h"
YamlParser::YamlParser() {
}


void YamlParser::loadDataStage(const std::string &aStageName, float& height, float& length, std::vector<Beam>& aBeams) {
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string stgNamNoSpace = aStageName;
    stgNamNoSpace.erase(std::remove(stgNamNoSpace.begin(), stgNamNoSpace.end(), ' '), stgNamNoSpace.end());
    std::string fullPath(startPath + "/Worms-Taller-1" + "/Stages/"+ stgNamNoSpace + ".yaml");
    YAML::Node node = YAML::LoadFile(fullPath);

    height = node["height"].as<float>();
    length = node["width"].as<float>();
    aBeams = getBeams(node["beams"]);
}

std::vector<std::string> YamlParser::getScenarioNames() {
    std::vector<std::string> scenarioNames;

    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string fullPath(startPath + "/Worms-Taller-1" + "/Stages/"+ "StageNames" + ".yaml");
    try{
        YAML::Node config = YAML::LoadFile(fullPath);
        for (const auto& scenario : config["namesScenarios"]) {
            auto name = scenario["name"].as<std::string>();
            scenarioNames.push_back(name);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return scenarioNames;
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
        if(length == 3.0){
            typeBeam = TypeBeam::SHORT_BEAM;
        } else if ( length == 6.0){
            typeBeam = TypeBeam::LONG_BEAM;
        } else if (length == 1500.0){
            typeBeam = TypeBeam::WATER_BEAM;
        }
        Beam beam(typeBeam, xCenter, yCenter, length, height, angle);
        beams.push_back(beam);
    }
    return beams;
}


