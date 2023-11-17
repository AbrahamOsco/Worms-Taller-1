//
// Created by riclui on 25/10/23.
//

#include "Worm.h"
#include "../../command/ChargeCmd.h"
#include "../../command/FireCmd.h"
#include "../../command/TeleportCmd.h"

Worm::Worm(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
           const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrosshair, int yCrosshair,
           const TypeSight &typeSight) : GameObject(LoaderParams(x, y, 60, 60, "player")), m_hpWorm(hpWorm),
                                         m_directionLook(direction),
                                         m_typeFocus(focus), m_moveWorm(moveWorm), m_weaponCurrent(weaponCurrent),
                                         m_xCrosshair(xCrosshair), m_yCrosshair(yCrosshair), m_typeSight(typeSight),
                                         m_animation(true) {
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
    m_animation.setProps(m_textureID, 14, 140);
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";

    std::string text = std::to_string(m_hpWorm);
    int fontSize = 11;

    SDL2pp::Font font(fontPath, fontSize);
    SDL2pp::Texture textTexture(renderer, font.RenderText_Blended(text, textColor));

    int textWidth = textTexture.GetWidth();

    textureManager.drawLife(text, m_x - textWidth / 2, m_y - 30, fontPath, fontSize, textColor, boxColor,
                               renderer, camera);
    if (m_weaponCurrent == TypeWeapon::DYNAMITE || m_weaponCurrent == TypeWeapon::AIR_ATTACK ||
        m_weaponCurrent == TypeWeapon::BASEBALL_BAT || m_weaponCurrent == TypeWeapon::NONE_WEAPON) {
        m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_width, m_height, camera, renderer, textureManager, m_flip);
    } else {
        int frameCount = 30;
        int angle = calcularAngulo(m_x, m_y, m_xCrosshair, m_yCrosshair, m_directionLook);
        angle = std::max(-90, std::min(90, angle));
        int rowIndex = static_cast<int>(((90 - angle) * frameCount) / 180);

        int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
        int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

        textureManager.drawFrame(m_textureID, xCorrection, yCorrection, m_width, m_height, rowIndex, 0,
                                 renderer, m_flip);
    }
}

void Worm::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) {
    if (m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }

    if (m_weaponCurrent == TypeWeapon::BASEBALL_BAT) {
        if (input.getKeyDown(SDL_SCANCODE_SPACE)) {
            std::unique_ptr<Command> command(new FireCmd());
            queue.move_push(std::move(command));
        }
    }

    if (m_weaponCurrent == TypeWeapon::TELEPORT) {
        if (input.isMouseRightButtonDown()) {
            SDL2pp::Point point(input.getMouseX(), input.getMouseY());
            SDL2pp::Point newPoint = point + camera.getPosition();
            std::cout << "send: " << newPoint << std::endl;
            std::unique_ptr<Command> command(new TeleportCmd(newPoint.GetX(), newPoint.GetY()));
            queue.move_push(std::move(command));
        }
    }

    animationState();
    m_animation.update();

    if(m_typeFocus == TypeFocusWorm::FOCUS) {
        SDL2pp::Point point(m_x, m_y);
        camera.setTarget(point);
    }
}

void Worm::animationState() {
    if (m_moveWorm == MoveWorm::WALKING) {
        m_width = 30;
        m_height = 30;
        m_animation.setProps("walk",14, 54);
    }
    if (m_moveWorm == MoveWorm::JUMPING) {
        m_width = 60;
        m_height = 60;
        m_animation.setProps("air",36, 60);
    }

    if(m_moveWorm == MoveWorm::ATTACKING_WITH_BAT) {
        m_width = 60;
        m_height = 30;
        m_animation.setProps("bat_hit", 15, 30);
    }
}

int Worm::calcularAngulo(int x, int y, int xCrosshair, int yCrosshair, const Direction &direction) {
    int dx = xCrosshair - x;
    int dy = yCrosshair - y;

    double radianes;

    if (direction == Direction::RIGHT) {
        radianes = std::atan2(dy, dx);
    } else {
        radianes = std::atan2(dy, -dx);
    }

    int grados = static_cast<int>(radianes * (180.0 / M_PI));

    return grados;
}
