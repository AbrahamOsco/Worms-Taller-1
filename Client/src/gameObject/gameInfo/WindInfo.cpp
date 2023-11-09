//
// Created by riclui on 09/11/23.
//

#include "WindInfo.h"

WindInfo::WindInfo(const LoaderParams &params, int velocity, Direction direction) : GameObject(params),
                                                                                    m_velocity(velocity),
                                                                                    m_direction(direction) {}

void WindInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {

}
