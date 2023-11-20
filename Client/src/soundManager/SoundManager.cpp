//
// Created by riclui on 20/11/23.
//

#include "SoundManager.h"

void SoundManager::playMusic(const std::string &id) {
    auto it = m_musicMap.find(id);
    if (it != m_musicMap.end()) {
        Mix_PlayMusic(it->second->Get(), 0);
    }
}

void SoundManager::LoadMusic(const std::string &id, const std::string &source) {
    m_musicMap[id] = std::make_unique<SDL2pp::Music>(source);
}

void SoundManager::playEffect(const std::string &id) {
    auto it = m_effectMap.find(id);
    if (it != m_effectMap.end()) {
        Mix_PlayChannel(-1, it->second->Get(), 0);
    }
}

void SoundManager::LoadEffect(const std::string &id, const std::string &source) {
    m_effectMap[id] = std::make_unique<SDL2pp::Chunk>(source);
}
