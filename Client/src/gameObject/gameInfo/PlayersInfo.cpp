//
// Created by riclui on 09/11/23.
//

#include "PlayersInfo.h"

PlayersInfo::PlayersInfo() : GameObject(LoaderParams(10, 140, 0, 0, " ")) {}

void PlayersInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    verticalAligned(10);
    for (PlayerInfo &player : m_players) {
        player.draw(renderer, textureManager, camera);
    }
}

void PlayersInfo::addPlayer(PlayerInfo &player) {
    m_players.push_back(player);
}

void PlayersInfo::verticalAligned(int verticalSpacing) {
    int yPos = m_y;  // Comenzar desde la posición y inicial

    for (PlayerInfo& player : m_players) {
        player.setParams(m_x, yPos);
        yPos += player.getHeight() + verticalSpacing;
    }
}
