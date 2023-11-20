//
// Created by riclui on 19/11/23.
//

#include "WormGuidedWeapon.h"
#include "../../command/TeleportCmd.h"
#include "../../soundManager/SoundManager.h"

WormGuidedWeapon::WormGuidedWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                                   const TypeFocusWorm &focus, const MoveWorm &moveWorm,
                                   const TypeWeapon &weaponCurrent, bool isMyTurn) : Worm(id, x, y, hpWorm, direction,
                                                                           focus, moveWorm, isMyTurn), m_weaponCurrent(weaponCurrent) {
    if (m_weaponCurrent == TypeWeapon::TELEPORT) {
        m_width = 30;
        m_height = 30;
        m_textureID = "teleportation";
    } else {
        std::cerr << "weapon not found" << std::endl;
    }
    m_animation.setProps(m_textureID, 14, 140);
}

void WormGuidedWeapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Worm::draw(renderer, textureManager, camera);
    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

    m_animation.draw(xCorrection, yCorrection, m_width, m_height, renderer, textureManager, m_flip);
}

void WormGuidedWeapon::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera,
                              SoundManager &soundManager) {
    Worm::update(input, queue, camera, soundManager);
    if (input.isMouseRightButtonDown()) {
        SDL2pp::Point point(input.getMouseX(), input.getMouseY());
        SDL2pp::Point newPoint = point + camera.getPosition();
        std::cout << "send: " << newPoint << std::endl;
        std::unique_ptr<Command> command(new TeleportCmd(newPoint.GetX(), newPoint.GetY()));
        queue.move_push(std::move(command));
    }
}
