//
// Created by riclui on 18/11/23.
//

#include "WormNoWeapon.h"

WormNoWeapon::WormNoWeapon(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
                           const MoveWorm &moveWorm) : Worm(x, y, hpWorm, direction, focus, moveWorm) {

}

void WormNoWeapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    Worm::draw(renderer, textureManager, camera);
    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();

    m_animation.draw(xCorrection, yCorrection, m_width, m_height, renderer, textureManager, m_flip);
}

void WormNoWeapon::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) {
    Worm::update(dt, input, queue, camera);
}
