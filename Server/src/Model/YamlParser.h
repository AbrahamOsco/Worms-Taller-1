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

    static Stage getStage(const std::string& aStageName);


};


#endif //WORMS_TALLER_1_YAMLPARSER_H
