//
// Created by riclui on 09/11/23.
//

#include "GameInfo.h"
#include "../../command/RightCmd.h"
#include "../../command/LeftCmd.h"
#include "../../command/JumpForwardCmd.h"
#include "../../command/JumpBackwardCmd.h"
#include "../../utils/Constants.h"

GameInfo::GameInfo(PlayersInfo &players, WeaponInventory &weaponInventory, WindInfo &wind, GameState &gameState, TypeResult &typeResult,
                   const std::string &currentTurn, int time) : GameObject(LoaderParams(0, 10, 0, 0, "arrow_no")), m_players(players),
                                    m_weaponInventory(weaponInventory),
                                    m_wind(wind), m_currentTurn(currentTurn), m_time(time), m_isMyTurn(false), m_gameState(gameState), m_typeResult(typeResult) {
    if(m_currentTurn == "Es tu turno") {
        m_isMyTurn = true;
    }
}

void GameInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    m_players.draw(renderer, textureManager, camera);
    m_weaponInventory.draw(renderer, textureManager, camera);
    m_wind.draw(renderer, textureManager, camera);

    int fontSize = 22;
    SDL_Color textColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawText(m_currentTurn, 200, m_y, fontPath, fontSize, textColor, renderer);
    textureManager.drawText("Time: " + std::to_string(m_time), 750, m_y, fontPath, fontSize, textColor, renderer);

    if (m_gameState == GameState::GAME_END) {
        if (m_typeResult == TypeResult::WON_THE_GAME) {
            textureManager.draw("victory", 100, 100, 1876, 1208, renderer);
        } else {
            textureManager.draw("defect", 100, 100, 1800, 1142, renderer);
        }
    }

}

void GameInfo::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) {
    m_weaponInventory.update(input, queue, camera);
    if (m_isMyTurn) {
        //m_weaponInventory.update(dt, input, queue, camera);
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
