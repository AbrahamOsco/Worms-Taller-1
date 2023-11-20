//
// Created by riclui on 09/11/23.
//

#include "WeaponInventory.h"
#include "../../utils/Constants.h"
#include "../../soundManager/SoundManager.h"

WeaponInventory::WeaponInventory() : GameObject(LoaderParams(WINDOW_WIDTH - 120, 40, 0, 0, " ")) {}

void WeaponInventory::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    //verticalAligned(10);
    for (WeaponIcon &weapon: m_weapons) {
        weapon.draw(renderer, textureManager, camera);
    }
}

void WeaponInventory::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera,
                             SoundManager &soundManager) {
    verticalAligned(10);
    for (WeaponIcon &weapon: m_weapons) {
        weapon.update(input, queue, camera, soundManager);
    }
}

void WeaponInventory::addWeapon(WeaponIcon &weapon) {
    m_weapons.push_back(weapon);
}

void WeaponInventory::verticalAligned(int verticalSpacing) {
    int yPos = m_y;

    for (WeaponIcon &weapon: m_weapons) {
        weapon.setParams(m_x, yPos);
        yPos += weapon.getHeight() + verticalSpacing;
    }
}




