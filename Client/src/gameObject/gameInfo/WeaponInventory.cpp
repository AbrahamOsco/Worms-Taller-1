//
// Created by riclui on 09/11/23.
//

#include "WeaponInventory.h"

WeaponInventory::WeaponInventory(const LoaderParams &params, std::vector<Weapon> &weapons) : GameObject(params), m_weapons(weapons) {}
