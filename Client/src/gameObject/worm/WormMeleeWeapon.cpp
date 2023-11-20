//
// Created by riclui on 19/11/23.
//

#include "WormMeleeWeapon.h"
#include "../../command/FireCmd.h"

WormMeleeWeapon::WormMeleeWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                                 const TypeFocusWorm &focus, const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, bool isMyTurn) : Worm(id, x, y, hpWorm, direction,
                                                                                              focus, moveWorm, isMyTurn), m_weaponCurrent(weaponCurrent) {
    if (m_weaponCurrent == TypeWeapon::BASEBALL_BAT) {
        m_width = 40;
        m_height = 30;
        m_textureID = "bat";
    } else {
        std::cerr << "weapon not found" << std::endl;
    }
    m_animation.setProps(m_textureID, 31, 140);
}

void WormMeleeWeapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Worm::draw(renderer, textureManager, camera);
    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

    m_animation.draw(xCorrection, yCorrection, m_width, m_height, renderer, textureManager, m_flip);
}

void WormMeleeWeapon::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera,
                             SoundManager &soundManager) {
    Worm::update(input, queue, camera, soundManager);
    if (input.getKeyDown(SDL_SCANCODE_SPACE)) {
        std::unique_ptr<Command> command(new FireCmd());
        queue.move_push(std::move(command));
    }
}
