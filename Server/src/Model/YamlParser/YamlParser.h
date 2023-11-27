//
// Created by abraham on 30/10/23.
//

#ifndef WORMS_TALLER_1_YAMLPARSER_H
#define WORMS_TALLER_1_YAMLPARSER_H

#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <utility>
#include <map>
#include <vector>
#include <string>
#include <linux/limits.h>
#include "../Scenario/Stage/Stage.h"
#include "../Scenario/Beam/Beam.h"


class YamlParser{
 private:
    static std::vector<Beam> getBeams(const YAML::Node& beamsNode);

 public:
    YamlParser();

    static void loadDataStage(const std::string &aStageName, float &height, float &length, std::vector<Beam> &aBeams,
                              std::map<size_t, std::pair<float, float>> &positionsWorms, std::string &background);

    static void getScenarioAndMaxWorms(std::vector<std::string>& vecScenarios, std::vector<size_t>& vecMaxNumberWorms);

    static size_t getNumberWorms(const std::string& aStageName);
};


#endif  // WORMS_TALLER_1_YAMLPARSER_H
