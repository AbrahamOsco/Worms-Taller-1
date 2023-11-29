//
// Created by riclui on 20/11/23.
//

#include "SoundManager.h"

void SoundManager::parseSounds(const std::string &source) {
    try {
        YAML::Node config = YAML::LoadFile(source);

        // Cargar música desde el YAML
        for (const auto &music : config["sounds"]["music"]) {
            std::string id = music["id"].as<std::string>();
            std::string sourceMusic = music["source"].as<std::string>();
            loadMusic(id, sourceMusic);
        }

        // Cargar efectos de sonido desde el YAML
        for (const auto &effect : config["sounds"]["effects"]) {
            std::string id = effect["id"].as<std::string>();
            std::string sourceEffect = effect["source"].as<std::string>();
            loadEffect(id, sourceEffect);
        }
    } catch (const YAML::Exception &e) {
        std::cerr << "Error al analizar el archivo YAML: " << e.what() << std::endl;
        // Manejar el error como sea necesario
    }
}

void SoundManager::playMusic(const std::string &id) {
    auto it = m_musicMap.find(id);
    if (it != m_musicMap.end()) {
        Mix_PlayMusic(it->second->Get(), 0);
    }
}

void SoundManager::loadMusic(const std::string &id, const std::string &source) {
    m_musicMap[id] = std::make_unique<SDL2pp::Music>(source);
}

void SoundManager::playEffect(const std::string &id) {
    auto it = m_effectMap.find(id);
    if (it != m_effectMap.end()) {
        Mix_PlayChannel(-1, it->second->Get(), 0);
    }
}

void SoundManager::loadEffect(const std::string &id, const std::string &source) {
    m_effectMap[id] = std::make_unique<SDL2pp::Chunk>(source);
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
}
