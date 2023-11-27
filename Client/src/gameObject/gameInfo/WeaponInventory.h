//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONINVENTORY_H
#define WORMS_TALLER_1_WEAPONINVENTORY_H

#include <memory>
#include <vector>
#include "../GameObject.h"
#include "../weaponIcon/WeaponIcon.h"

class WeaponInventory : GameObject {
 private:
    std::vector<WeaponIcon> m_weapons;
 public:
    WeaponInventory();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;

    void addWeapon(WeaponIcon &weapon);

    void verticalAligned(int verticalSpacing);
};


#endif  // WORMS_TALLER_1_WEAPONINVENTORY_H
