//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_SOUNDMANAGER_H
#define WORMS_TALLER_1_SOUNDMANAGER_H


#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "SDL2pp/Chunk.hh"
#include "SDL2pp/Music.hh"
#include <yaml-cpp/yaml.h>

class SoundManager {
private:
    std::map<std::string, std::unique_ptr<SDL2pp::Chunk>> m_effectMap;
    std::map<std::string, std::unique_ptr<SDL2pp::Music>> m_musicMap;
public:
    void parseSounds(const std::string &source);

    void playMusic(const std::string &id);
    void loadMusic(const std::string &id, const std::string &source);

    void playEffect(const std::string &id);
    void loadEffect(const std::string &id, const std::string &source);
};


#endif //WORMS_TALLER_1_SOUNDMANAGER_H
