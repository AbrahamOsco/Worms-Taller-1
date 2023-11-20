//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_SOUNDMANAGER_H
#define WORMS_TALLER_1_SOUNDMANAGER_H


#include <string>
#include <map>
#include <memory>
#include "SDL2pp/Chunk.hh"
#include "SDL2pp/Music.hh"

class SoundManager {
private:
    std::map<std::string, std::unique_ptr<SDL2pp::Chunk>> m_effectMap;
    std::map<std::string, std::unique_ptr<SDL2pp::Music>> m_musicMap;
public:
    void playMusic(const std::string &id);
    void LoadMusic(const std::string &id, const std::string &source);

    void playEffect(const std::string &id);
    void LoadEffect(const std::string &id, const std::string &source);
};


#endif //WORMS_TALLER_1_SOUNDMANAGER_H
