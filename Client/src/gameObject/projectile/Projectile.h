//
// Created by riclui on 14/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILE_H
#define WORMS_TALLER_1_PROJECTILE_H

#include <memory>
#include "../GameObject.h"
#include "../../soundManager/SoundManager.h"
#include "../../animation/SpriteAnimation.h"

class Projectile : public GameObject {
    TypeProjectil m_typeProjectile;
    TypeFocus m_typeFocus;
    TypeExplode m_typeExplode;
    SpriteAnimation m_animation;

 public:
    Projectile(int x, int y, const TypeProjectil &typeProjectile, const TypeFocus &typeFocus,
                const TypeExplode &typeExplode);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif  // WORMS_TALLER_1_PROJECTILE_H
