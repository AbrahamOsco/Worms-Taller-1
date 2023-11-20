//
// Created by riclui on 25/10/23.
//

#include "Worm.h"
#include "../../command/ChargeCmd.h"
#include "../../command/FireCmd.h"
#include "../../command/TeleportCmd.h"
#include "../../utils/ColorDefinitions.h"
#include "../../command/RightCmd.h"
#include "../../command/LeftCmd.h"
#include "../../command/JumpForwardCmd.h"
#include "../../command/JumpBackwardCmd.h"

Worm::Worm(int id, int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocus &focus,
           const MoveWorm &moveWorm, bool isMyTurn) : GameObject(LoaderParams(x, y, 60, 60, "player")), m_id(id), m_hpWorm(hpWorm),
                                       m_directionLook(direction), m_typeFocus(focus), m_moveWorm(moveWorm),
                                       m_animation(true), m_isMyTurn(isMyTurn) {
    m_flip = SDL_FLIP_NONE;
    m_animation.setProps(m_textureID, 14, 140);

    if (m_moveWorm == MoveWorm::WALKING) {
        m_width = 30;
        m_height = 30;
        m_animation.setProps("walk", 14, 54);
    }
    if (m_moveWorm == MoveWorm::JUMPING) {
        m_width = 60;
        m_height = 60;
        m_animation.setProps("air", 36, 60);
    }

    if (m_moveWorm == MoveWorm::ATTACKING_WITH_BAT) {
        m_width = 60;
        m_height = 30;
        m_animation.setProps("bat_hit", 15, 30);
    }
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = colorMap[static_cast<ColorID>(m_id)];
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";

    int xCorrection;
    int yCorrection;

    std::string text = std::to_string(m_hpWorm);
    int fontSize = 11;

    SDL2pp::Font font(fontPath, fontSize);
    SDL2pp::Texture textTexture(renderer, font.RenderText_Blended(text, textColor));

    int textWidth = textTexture.GetWidth();

    xCorrection = m_x - textWidth / 2 - camera.getPosition().GetX();
    yCorrection = m_y - 30 - camera.getPosition().GetY();

    textureManager.drawTextBox(text, xCorrection, yCorrection, fontPath, fontSize, textColor, boxColor, renderer);
}

void Worm::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }

    m_animation.update();

    if (m_typeFocus == TypeFocus::FOCUS) {
        SDL2pp::Point point(m_x, m_y);
        camera.setTarget(point);
    }

    if (m_isMyTurn && m_typeFocus == TypeFocus::FOCUS) {
        if (input.getKeyDown(SDL_SCANCODE_RIGHT)) {
            std::unique_ptr<Command> command(new RightCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_LEFT)) {
            std::unique_ptr<Command> command(new LeftCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_RETURN)) {
            soundManager.playEffect("jump");
            std::unique_ptr<Command> command(new JumpForwardCmd());
            queue.move_push(std::move(command));
        } else if (input.getKeyDown(SDL_SCANCODE_BACKSPACE)) {
            soundManager.playEffect("jump");
            std::unique_ptr<Command> command(new JumpBackwardCmd());
            queue.move_push(std::move(command));
        }
    }
}