//
// Created by abraham on 30/10/23.
//

#include "YamlParser.h"
YamlParser::YamlParser() {
}


Stage YamlParser::getStage(const std::string &aStageName) {
    // busco el path del archivo
    // hay que cambiarlo para la implementacion de verdad
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    std::string toErase("/Server");
    unsigned long startPos = startPath.find(toErase);
    startPath.erase(startPos,toErase.length());
    std::string fullPath(startPath + "/Stages/"+ aStageName + ".yaml");

    YAML::Node node = YAML::LoadFile(fullPath);

    std::vector<Beam> beams = getBeams(node["beams"]);

    size_t height = node["height"].as<float>();
    size_t length = node["width"].as<float>();

    Stage stage(aStageName,height, length, beams);

    return stage;
}

std::vector<Beam> YamlParser::getBeams(const YAML::Node &beamsNode) {
    std::vector<Beam> beams;
    for (YAML::const_iterator it = beamsNode.begin(); it != beamsNode.end(); ++it) {
        const YAML::Node& beamNode = *it;
        auto length = beamNode["length"].as<float>();
        auto angle = beamNode["angle"].as<float>();
        auto posX = beamNode["x"].as<float>();
        auto posY = beamNode["y"].as<float>();

        Beam beam = Beam();
        beams.push_back(beam);
    }
    return beams;
}

