//
// Created by riclui on 09/11/23.
//

#include "WeaponInventory.h"
#include "../../utils/Constants.h"

WeaponInventory::WeaponInventory() : GameObject(LoaderParams(WINDOW_WIDTH - 120, 40, 0, 0, " ")) {}

void WeaponInventory::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    //verticalAligned(10);
    for (Weapon &weapon: m_weapons) {
        weapon.draw(renderer, textureManager);
    }
}

void WeaponInventory::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    verticalAligned(10);
    for (Weapon &weapon: m_weapons) {
        weapon.update(dt, input, queue);
    }
}

void WeaponInventory::addWeapon(Weapon &weapon) {
    m_weapons.push_back(weapon);
}

void WeaponInventory::verticalAligned(int verticalSpacing) {
    int yPos = m_y;

    for (Weapon &weapon: m_weapons) {
        weapon.setParams(m_x, yPos);
        yPos += weapon.getHeight() + verticalSpacing;
    }
}




