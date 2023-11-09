//
// Created by riclui on 09/11/23.
//

#include "GameInfo.h"
#include "../../command/RightCmd.h"
#include "../../command/LeftCmd.h"
#include "../../command/JumpForwardCmd.h"
#include "../../command/JumpBackwardCmd.h"

GameInfo::GameInfo(const LoaderParams &params, PlayersInfo &players, WeaponInventory &weaponInventory, WindInfo &wind,
                   const std::string &currentTurn,
                   bool isMyTurn) : GameObject(params), m_players(players), m_weaponInventory(weaponInventory),
                                    m_wind(wind), m_currentTurn(currentTurn), m_isMyTurn(isMyTurn) {}

void GameInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    m_players.draw(renderer, textureManager);
    m_weaponInventory.draw(renderer,textureManager);
    m_wind.draw(renderer, textureManager);

    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawText(m_currentTurn, 20, 20, 20, 20, fontPath, 12, textColor, boxColor, renderer);
}

void GameInfo::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    if (m_isMyTurn) {
        m_weaponInventory.update(dt, input, queue);

        if (input.getKeyDown(SDL_SCANCODE_RIGHT)) {
            std::unique_ptr<Command> command(new RightCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_LEFT)) {
            std::unique_ptr<Command> command(new LeftCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_RETURN)) {
            std::unique_ptr<Command> command(new JumpForwardCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_BACKSPACE)) {
            std::unique_ptr<Command> command(new JumpBackwardCmd());
            queue.move_push(std::move(command));
        }
    }
}
