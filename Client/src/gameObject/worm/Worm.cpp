//
// Created by riclui on 25/10/23.
//

#include "Worm.h"
#include "../../command/ChargeCmd.h"
#include "../../command/FireCmd.h"

Worm::Worm(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
           const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrosshair, int yCrosshair, const TypeSight &typeSight) : GameObject(LoaderParams(x, y, 60, 60, "player")), m_hpWorm(hpWorm), m_directionLook(direction),
                                       m_typeFocus(focus), m_moveWorm(moveWorm), m_weaponCurrent(weaponCurrent), m_xCrosshair(xCrosshair), m_yCrosshair(yCrosshair), m_typeSight(typeSight) {
    m_flip = SDL_FLIP_NONE;
    if (m_weaponCurrent == TypeWeapon::NONE_WEAPON) {
        m_width = 60;
        m_height = 60;
        m_textureID = "player";
    } else if (m_weaponCurrent == TypeWeapon::BAZOOKA) {
        m_width = 30;
        m_height = 30;
        m_textureID = "bazooka";
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
    if (m_weaponCurrent == TypeWeapon::DYNAMITE || m_weaponCurrent == TypeWeapon::AIR_ATTACK || m_weaponCurrent == TypeWeapon::BASEBALL_BAT || m_weaponCurrent == TypeWeapon::NONE_WEAPON) {
        m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_flip, renderer, textureManager);
    } else {
        int angle = calcularAngulo(m_x, m_y, m_xCrosshair,m_yCrosshair);

        // Asegurarte de que el ángulo esté dentro del rango -90 a 90 grados
        angle = std::max(-90, std::min(90, angle));

        int numRows = 30;
        // Convertir el ángulo a un índice de fila en tu sprite sheet
        int rowIndex = 30 - static_cast<int>((angle + 90.0) / 180.0 * numRows);

        textureManager.drawFrame(m_textureID, m_x - m_width / 2, m_y - m_height / 2, m_width, m_height, rowIndex, 0, renderer,m_flip);
    }
}

void Worm::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    if (m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }

    if (m_weaponCurrent == TypeWeapon::BASEBALL_BAT) {
        if (input.getKeyDown(SDL_SCANCODE_SPACE)) {
            std::unique_ptr<Command> command(new FireCmd());
            queue.move_push(std::move(command));
        }
    }

    animationState();
    m_animation.update();
}

void Worm::animationState() {
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
    if(m_moveWorm == MoveWorm::ATTACKING) {
        m_width = 60;
        m_height = 30;
        m_animation.setProps("bat_hit", m_width, m_height, 15, 30, SDL_FLIP_NONE);
    }
}

int Worm::calcularAngulo(int x, int y, int xCrosshair, int yCrosshair) {
    int dx = xCrosshair - x;
    int dy = yCrosshair - y;

    // Calcular el ángulo en radianes
    double radianes = std::atan2(dy, dx);

    // Convertir radianes a grados
    int grados = static_cast<int>(radianes * (180.0 / M_PI));

    return grados;
}
