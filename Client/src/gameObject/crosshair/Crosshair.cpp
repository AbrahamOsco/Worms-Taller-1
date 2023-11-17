//
// Created by riclui on 13/11/23.
//

#include "Crosshair.h"
#include "../../command/ChargeCmd.h"
#include "../../command/FireCmd.h"
#include "../../command/UpCmd.h"
#include "../../command/DownCmd.h"

Crosshair::Crosshair(int x, int y, const TypeSight &typeSight) : GameObject(LoaderParams(x, y, 60, 60, "crosshair")), m_typeSight(typeSight),
                                                                 m_animation(true) {
    m_animation.setProps(m_textureID, 32, 60);
}

void Crosshair::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    if (m_typeSight == TypeSight::SHOW_SIGHT) {
        m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_width, m_height,camera, renderer, textureManager);
    }
}

void Crosshair::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) {
    m_animation.update();
    if (m_typeSight == TypeSight::SHOW_SIGHT) {
        if (input.getKeyDown(SDL_SCANCODE_UP)) {
            std::unique_ptr<Command> command(new UpCmd());
            queue.move_push(std::move(command));
        }

        if (input.getKeyDown(SDL_SCANCODE_DOWN)) {
            std::unique_ptr<Command> command(new DownCmd());
            queue.move_push(std::move(command));
        }

        if (input.getKeyDown(SDL_SCANCODE_SPACE)) {
            std::cout << "disparo" << std::endl;
            std::unique_ptr<Command> command(new FireCmd());
            queue.move_push(std::move(command));
        }

        /*if (input.getKeyUp(SDL_SCANCODE_SPACE) && input.getPrevSpaceState()) {
            std::cout << "disparo" << std::endl;
            std::unique_ptr<Command> command(new FireCmd());
            queue.move_push(std::move(command));
        }*/
    }
}

