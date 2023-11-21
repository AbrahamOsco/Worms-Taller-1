//
// Created by riclui on 19/11/23.
//

#include "WormMeleeWeapon.h"
#include "../../command/FireCmd.h"

WormMeleeWeapon::WormMeleeWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                                 const TypeFocus &focus, const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent,
                                 int xCrossHair, int yCrossHair, const TypeSight &typeSight, bool isMyTurn) : Worm(id,
                                                                                                                   x, y,
                                                                                                                   hpWorm,
                                                                                                                   direction,
                                                                                                                   focus,
                                                                                                                   moveWorm,
                                                                                                                   isMyTurn),
                                                                                                              m_weaponCurrent(
                                                                                                                      weaponCurrent),
                                                                                                              m_crossHair(
                                                                                                                      xCrossHair,
                                                                                                                      yCrossHair,
                                                                                                                      typeSight) {

    if (m_weaponCurrent == TypeWeapon::BASEBALL_BAT) {
        m_width = 40;
        m_height = 30;
        m_textureID = "bat";
        m_animation.setProps(m_textureID, 31, 140);
    } else if (m_weaponCurrent == TypeWeapon::DYNAMITE_HOLDER) {
        m_width = 30;
        m_height = 30;
        m_textureID = "dynamite";
        m_animation.setProps(m_textureID, 31, 60);
    } else {
        std::cerr << "weapon not found" << std::endl;
    }

}

void WormMeleeWeapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Worm::draw(renderer, textureManager, camera);

    m_crossHair.draw(renderer, textureManager, camera);

    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

    m_animation.draw(xCorrection, yCorrection, m_width, m_height, renderer, textureManager, m_flip);
}

void WormMeleeWeapon::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera,
                             SoundManager &soundManager) {
    Worm::update(input, queue, camera, soundManager);
    m_crossHair.update(input, queue, camera, soundManager);

    if (input.getKeyDown(SDL_SCANCODE_SPACE) && m_isMyTurn) {
        soundManager.playEffect("bat");
        std::unique_ptr<Command> command(new FireCmd());
        queue.move_push(std::move(command));
    }
}
