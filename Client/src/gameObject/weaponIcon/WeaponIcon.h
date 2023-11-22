//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONICON_H
#define WORMS_TALLER_1_WEAPONICON_H


#include "../GameObject.h"

class WeaponIcon : public GameObject {
private:
    TypeWeapon m_typeWeapon;
    TypeMunition m_typeMunition;
    int m_ammoCount;
    bool m_isSelected;
    bool m_isMyTurn;
public:
    WeaponIcon(TypeWeapon typeWeapon, int ammoCount, const TypeMunition &typeMunition, const TypeWeapon &currentWeapon, bool isMyTurn);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;

    void setParams(int x, int y);

    int getHeight();
};


#endif //WORMS_TALLER_1_WEAPONICON_H
