//
// Created by abraham on 30/10/23.
//

#ifndef WORMS_TALLER_1_YAMLPARSER_H
#define WORMS_TALLER_1_YAMLPARSER_H

#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <linux/limits.h>
#include "Stage.h"
#include "Beam.h"


class YamlParser{
private:
    static std::vector<Beam> getBeams(const YAML::Node& beamsNode);

public:

    YamlParser();

    static void loadDataStage(const std::string &aStageName, float &height, float &length, std::vector<Beam> &aBeams,
                              std::map<size_t, std::pair<float, float>> &positionsWorms);

    static std::vector<std::string> getScenarioNames();
};


#endif //WORMS_TALLER_1_YAMLPARSER_H
