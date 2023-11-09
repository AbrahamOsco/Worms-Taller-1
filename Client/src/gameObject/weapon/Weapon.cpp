//
// Created by riclui on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(const LoaderParams &params, const std::string &weapon, int ammoCount) : GameObject(params),
                                                                                       m_weapon(weapon),
                                                                                       m_ammoCount(ammoCount) {}
