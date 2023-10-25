//
// Created by riclui on 25/10/23.
//

#include "TextureManager.h"

void TextureManager::load(std::string& fileName, std::string& id, SDL2pp::Renderer& renderer) {
    try {
        // Cargar la textura usando SDL2pp
        SDL2pp::Surface surface(fileName);
        std::unique_ptr<SDL2pp::Texture> texture = std::make_unique<SDL2pp::Texture>(renderer, surface);

        // Almacenar la textura en el mapa con el ID proporcionado
        m_textureMap[id] = std::move(texture);
    } catch (const SDL2pp::Exception& ex) {
        // Manejar excepciones en caso de error
        std::cerr << "Error al cargar la textura" << std::endl;
    }
}

void
TextureManager::draw(std::string& id, int x, int y, int width, int height, SDL2pp::Renderer& renderer, SDL_RendererFlip flip) {
    // Buscar la textura por su ID
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture* texture = it->second.get();
        if (texture) {
            // Definir el rectángulo de origen (la textura completa)
            SDL2pp::Rect srcRect(0, 0, width, height);

            // Definir el rectángulo de destino (posición y tamaño en la ventana)
            SDL2pp::Rect destRect(x, y, width, height);

            // Dibujar la textura en el Renderer
            renderer.Copy(*texture, srcRect, destRect, 0.0, SDL2pp::NullOpt, flip);
        }
    }
}

void TextureManager::drawFrame(std::string& id, int x, int y, int width, int height, int currentRow, int currentCol,
                               SDL2pp::Renderer& renderer, SDL_RendererFlip flip) {
    // Buscar la textura por su ID
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture* texture = it->second.get(); // Obtener el puntero de la textura
        if (texture) {
            // Calcular la posición y tamaño del clip (recorte) en el sprite sheet
            SDL2pp::Rect srcRect(currentCol * width, currentRow * height, width, height);

            // Definir el rectángulo de destino (posición y tamaño en la ventana)
            SDL2pp::Rect destRect(x, y, width, height);

            // Dibujar la textura en el Renderer
            renderer.Copy(*texture, srcRect, destRect, 0.0, SDL2pp::NullOpt, flip);
        }
    }
}
