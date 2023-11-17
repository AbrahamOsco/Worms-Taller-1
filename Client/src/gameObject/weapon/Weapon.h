//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WEAPON_H
#define WORMS_TALLER_1_WEAPON_H


#include "../GameObject.h"

class Weapon : public GameObject {
private:
    TypeWeapon m_typeWeapon;
    int m_ammoCount;
    bool m_isSelected;
    bool m_isMyTurn;
public:
    Weapon(TypeWeapon typeWeapon, int ammoCount, const TypeWeapon &currentWeapon, bool isMyTurn);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) override;

    void setParams(int x, int y);

    int getHeight();
};


#endif //WORMS_TALLER_1_WEAPON_H
