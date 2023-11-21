//
// Created by riclui on 18/11/23.
//

#include "WormRangedWeapon.h"

WormRangedWeapon::WormRangedWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                                   const TypeFocus &focus, const MoveWorm &moveWorm,
                                   const TypeWeapon &weaponCurrent, int xCrossHair, int yCrossHair,
                                   const TypeSight &typeSight, bool isMyTurn) : Worm(id, x, y, hpWorm, direction, focus, moveWorm, isMyTurn),
                                                                 m_weaponCurrent(weaponCurrent),
                                                                 m_xCrossHair(xCrossHair), m_yCrossHair(yCrossHair),
                                                                 m_crossHair(xCrossHair, yCrossHair, typeSight) {
    if (m_weaponCurrent == TypeWeapon::BAZOOKA) {
        m_width = 30;
        m_height = 30;
        m_textureID = "bazooka";
    } else if (m_weaponCurrent == TypeWeapon::MORTAR) {
        m_width = 30;
        m_height = 30;
        m_textureID = "mortar";
    } else if (m_weaponCurrent == TypeWeapon::GREEN_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "green_grenade";
    } else if (m_weaponCurrent == TypeWeapon::RED_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "red_grenade";
    } else if (m_weaponCurrent == TypeWeapon::HOLY_GRENADE) {
        m_width = 30;
        m_height = 30;
        m_textureID = "holy_grenade";
    } else if (m_weaponCurrent == TypeWeapon::BANANA) {
        m_width = 30;
        m_height = 30;
        m_textureID = "banana";
    } else {
        std::cerr << "weapon not found" << std::endl;
    }
}

void WormRangedWeapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Worm::draw(renderer, textureManager, camera);

    m_crossHair.draw(renderer, textureManager, camera);

    int frameCount = 30;
    int angle = calculateAngle(m_x, m_y, m_directionLook);
    angle = std::max(-90, std::min(90, angle));
    int rowIndex = static_cast<int>(((90 - angle) * frameCount) / 180);

    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

    textureManager.drawFrame(m_textureID, xCorrection, yCorrection, m_width, m_height, rowIndex, 0,
                             renderer, m_flip);
}

void WormRangedWeapon::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera,
                              SoundManager &soundManager) {
    Worm::update(input, queue, camera, soundManager);
    m_crossHair.update(input, queue, camera,soundManager);
}

int WormRangedWeapon::calculateAngle(int x, int y, Direction direction) const {
    int dx = m_xCrossHair - x;
    int dy = m_yCrossHair - y;

    double radians;

    if (direction == Direction::RIGHT) {
        radians = std::atan2(dy, dx);
    } else {
        radians = std::atan2(dy, -dx);
    }

    int degrees = static_cast<int>(radians * (180.0 / M_PI));

    return degrees;
}
