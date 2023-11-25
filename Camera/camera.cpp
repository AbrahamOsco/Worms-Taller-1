#include <iostream>
#include <exception>
#include <algorithm>
#include <string>
#include <fstream>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

int main() {
    SDL sdl(SDL_INIT_VIDEO);
    int windowX = 600;
    int windowY = 600;
    int imageX = 10922;
    int imageY = 6000;
    Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        windowX, windowY, SDL_WINDOW_RESIZABLE);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    Texture sprites(renderer, Surface("../Camera/DF.jpg"));
    int x = (imageX - windowX)/2;
    int y = (imageY - windowY)/2;
    int mouseX = windowX/2;
    int mouseY = windowY/2;
    int margin = windowX/8;
    int move = 10;
    while (1) {
        renderer.Clear();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                    return 0;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
        }
        if (mouseX < ((windowX/2) - margin)) {
            x = std::max(0, x-move);
        }
        if (mouseX > ((windowX/2) + margin)) {
            x = std::min(imageX-windowX, x+move);
        }
        if (mouseY < ((windowX/2) - margin)) {
            y = std::max(0, y-move);
        }
        if (mouseY > ((windowX/2) + margin)) {
            y = std::min(imageY-windowY, y+move);
        }
        renderer.Copy(sprites, Rect(x, y, windowX, windowY), Rect(0, 0, imageX/10, imageY/10));
        renderer.Present();
        SDL_Delay(10);
    }
}
