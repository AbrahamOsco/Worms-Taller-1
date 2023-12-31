//
// Created by riclui on 09/11/23.
//

#include <string>
#include <utility>
#include "WeaponIcon.h"
#include "../../command/SelectTeleportCmd.h"
#include "../../command/SelectBatCmd.h"
#include "../../command/SelectBazookaCmd.h"
#include "../../soundManager/SoundManager.h"
#include "../../command/SelectAirAttackCmd.h"
#include "../../command/SelectMortarCmd.h"
#include "../../command/SelectGreenGrenadeCmd.h"
#include "../../command/SelectRedGrenadeCmd.h"
#include "../../command/SelectHolyGrenadeCmd.h"
#include "../../command/SelectBananaCmd.h"
#include "../../command/SelectDynamiteCmd.h"

WeaponIcon::WeaponIcon(TypeWeapon typeWeapon, int ammoCount, const TypeMunition &typeMunition,
                        const TypeWeapon &currentWeapon, bool isMyTurn): GameObject(LoaderParams(0, 0, 50, 55, " ")),
                        m_typeWeapon(typeWeapon), m_ammoCount(ammoCount), m_isSelected(false),
                        m_isMyTurn(isMyTurn), m_typeMunition(typeMunition) {
    if (m_typeWeapon == currentWeapon) {
        m_isSelected = true;
    }

    if (m_typeWeapon == TypeWeapon::AIR_ATTACK) {
        m_textureID = "air_attack_icon";
    } else if (m_typeWeapon == TypeWeapon::DYNAMITE_HOLDER) {
        m_textureID = "dynamite_icon";
    } else if (m_typeWeapon == TypeWeapon::RED_GRENADE) {
        m_textureID = "red_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::GREEN_GRENADE) {
        m_textureID = "green_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::BANANA) {
        m_textureID = "banana_icon";
    } else if (m_typeWeapon == TypeWeapon::TELEPORT) {
        m_textureID = "teleportation_icon";
    } else if (m_typeWeapon == TypeWeapon::BASEBALL_BAT) {
        m_textureID = "bat_icon";
    } else if (m_typeWeapon == TypeWeapon::HOLY_GRENADE) {
        m_textureID = "holy_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::BAZOOKA) {
        m_textureID = "bazooka_icon";
    } else if (m_typeWeapon == TypeWeapon::MORTAR) {
        m_textureID = "mortar_icon";
    }
}

void WeaponIcon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    SDL_Color boxColor = {255, 255, 255, 80};
    SDL_Color textColor = {0, 0, 0, 255};
    int fontSize = 16;
    int padding = 6;

    if (m_isSelected) {
        textColor = {0, 0, 255, 255};
    }
    if (m_ammoCount == 0) {
        textureManager.setColorMod(m_textureID, 255, 255, 255, 100);
    }
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);
    textureManager.resetColorMod(m_textureID);

    textureManager.drawTextBox("Ammo:", m_x + m_width + padding, m_y + 12, fontPath, fontSize,
        textColor, boxColor,    renderer);
    std::string text;
    if (m_typeMunition == TypeMunition::INFINITE) {
        text = "Inf";
    } else {
        text = std::to_string(m_ammoCount);
    }
    textureManager.drawTextBox(text, m_x + m_width + 20, m_y + 34, fontPath, fontSize, textColor, boxColor,
                            renderer);
}

void WeaponIcon::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int WeaponIcon::getHeight() {
    return m_height;
}

void
WeaponIcon::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (input.isMouseLeftButtonDown() && m_isMyTurn && m_ammoCount > 0) {
        SDL2pp::Rect shape = SDL2pp::Rect(m_x, m_y, m_width, m_height);
        SDL2pp::Point point(input.getMouseX(), input.getMouseY());
        if (SDL_PointInRect(&point, &shape) && !m_isSelected) {
            m_isSelected = true;
            soundManager.playEffect("select_weapon");
            if (m_typeWeapon == TypeWeapon::TELEPORT) {
                std::unique_ptr<Command> command(new SelectTeleportCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::BASEBALL_BAT) {
                std::unique_ptr<Command> command(new SelectBatCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::BAZOOKA) {
                std::unique_ptr<Command> command(new SelectBazookaCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::AIR_ATTACK) {
                std::unique_ptr<Command> command(new SelectAirAttackCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::MORTAR) {
                std::unique_ptr<Command> command(new SelectMortarCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::GREEN_GRENADE) {
                std::unique_ptr<Command> command(new SelectGreenGrenadeCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::RED_GRENADE) {
                std::unique_ptr<Command> command(new SelectRedGrenadeCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::HOLY_GRENADE) {
                std::unique_ptr<Command> command(new SelectHolyGrenadeCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::BANANA) {
                std::unique_ptr<Command> command(new SelectBananaCmd());
                queue.move_push(std::move(command));
            } else if (m_typeWeapon == TypeWeapon::DYNAMITE_HOLDER) {
                std::unique_ptr<Command> command(new SelectDynamiteCmd());
                queue.move_push(std::move(command));
            }
        }
    }
}



