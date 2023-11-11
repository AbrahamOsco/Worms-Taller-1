//
// Created by riclui on 25/10/23.
//

#include "Worm.h"

Worm::Worm(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
           const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent) : GameObject(LoaderParams(x, y, 60, 60, "player")), m_hpWorm(hpWorm), m_directionLook(direction),
                                       m_typeFocus(focus), m_moveWorm(moveWorm), m_weaponCurrent(weaponCurrent) {
    m_flip = SDL_FLIP_NONE;
    if (m_weaponCurrent == TypeWeapon::NONE_WEAPON) {
        m_width = 60;
        m_height = 60;
        m_textureID = "player";
    } else if (m_weaponCurrent == TypeWeapon::BAZOOKA) {
        m_width = 30;
        m_height = 30;
        m_textureID = "bazzoka";
    } else if (m_weaponCurrent == TypeWeapon::MORTAR) {
        m_width = 30;
        m_height = 30;
        m_textureID = "mortar";
    } else if (m_weaponCurrent == TypeWeapon::RED_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "red_grenade";
    } else if (m_weaponCurrent == TypeWeapon::GREEN_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "green_grenade";
    } else if (m_weaponCurrent == TypeWeapon::BANANA) {
        m_width = 30;
        m_height = 30;
        m_textureID = "banana";
    } else if (m_weaponCurrent == TypeWeapon::HOLY_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "holy_grenade";
    } else if (m_weaponCurrent == TypeWeapon::DYNAMITE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "dynamite";
    } else if (m_weaponCurrent == TypeWeapon::BASEBALL_BAT) {
        m_width = 40;
        m_height = 30;
        m_textureID = "bat";
    } else if (m_weaponCurrent == TypeWeapon::AIR_ATTACK) {
        m_width = 30;
        m_height = 30;
        m_textureID = "air_attack";
    } else if (m_weaponCurrent == TypeWeapon::TELEPORT) {
        m_width = 30;
        m_height = 30;
        m_textureID = "teleportation";
    } else {
        std::cout << "weapon not found" << std::endl;
    }
    m_animation.setProps(m_textureID, m_width, m_height, 14, 140);
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";

    std::string text = std::to_string(m_hpWorm);
    int fontSize = 11;

    SDL2pp::Font font(fontPath, fontSize);
    SDL2pp::Texture textTexture(renderer, font.RenderText_Blended(text, textColor));

    int textWidth = textTexture.GetWidth();

    textureManager.drawTextBox(text, m_x - textWidth/2, m_y - 30, fontPath, fontSize, textColor, boxColor,
                               renderer);
    m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_flip, renderer, textureManager);
}

void Worm::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    if (m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    animationState();
    m_animation.update();
}

void Worm::animationState() {
    //m_animation.setProps("player", m_width, m_height, 14, 140, SDL_FLIP_NONE);

    if (m_moveWorm == MoveWorm::WALKING) {
        m_width = 30;
        m_height = 30;
        m_animation.setProps("walk", m_width, m_height, 14, 54, SDL_FLIP_NONE);
    }
    if (m_moveWorm == MoveWorm::JUMPING) {
        m_width = 60;
        m_height = 60;
        m_animation.setProps("air", m_width, m_height, 36, 60, SDL_FLIP_NONE);
    }
}
