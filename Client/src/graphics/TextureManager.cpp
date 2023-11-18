//
// Created by riclui on 25/10/23.
//

#include "TextureManager.h"

void TextureManager::load(const std::string &fileName, std::string &id, SDL2pp::Renderer &renderer) {
    try {
        // Cargar la textura usando SDL2pp
        SDL2pp::Surface surface(fileName);
        std::unique_ptr<SDL2pp::Texture> texture = std::make_unique<SDL2pp::Texture>(renderer, surface);

        // Almacenar la textura en el mapa con el ID proporcionado
        m_textureMap[id] = std::move(texture);
    } catch (const SDL2pp::Exception &ex) {
        // Manejar excepciones en caso de error
        std::cerr << "Error al cargar la textura" << std::endl;
    }
}

void TextureManager::draw(const std::string &id, int x, int y, int width, int height, SDL2pp::Renderer &renderer,
                          SDL_RendererFlip flip) {
    // Buscar la textura por su ID
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get();
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

void
TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentCol,
                          SDL2pp::Renderer &renderer, SDL_RendererFlip flip) {
    // Buscar la textura por su ID
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get(); // Obtener el puntero de la textura
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

void TextureManager::parseTexture(const std::string &yamlFileName, SDL2pp::Renderer &renderer) {
    try {
        // Cargar el archivo YAML
        YAML::Node config = YAML::LoadFile(yamlFileName);

        // Acceder a la sección de texturas
        const YAML::Node &textures = config["textures"];

        // Iterar sobre las texturas y cargarlas
        for (const YAML::Node &texture: textures) {
            std::string name = texture["name"].as<std::string>();
            std::string source = texture["source"].as<std::string>();

            // Cargar la textura desde el archivo "source"
            load(source, name, renderer);
        }
    } catch (const YAML::Exception &ex) {
        std::cerr << "Error al analizar el archivo YAML: " << ex.what() << std::endl;
    }
}

void TextureManager::drawTextBox(const std::string &text, int x, int y, const std::string &fontPath, int fontSize,
                                 SDL_Color textColor, SDL_Color boxColor, SDL2pp::Renderer &renderer) {
    SDL2pp::Font font(fontPath, fontSize);
    SDL2pp::Texture textTexture(renderer, font.RenderText_Blended(text, textColor));

    int textWidth = textTexture.GetWidth();
    int textHeight = textTexture.GetHeight();

    // Calcular la posición del texto para que quede en el punto (x, y)
    int textX = x;
    int textY = y;

    int padding = 2;

    // Calcular la caja del texto basado en las dimensiones reales del texto
    SDL_Rect textBoxRect = {x - padding, y - padding, textWidth + 2 * padding, textHeight + 2 * padding};

    // Ajustar la posición de la caja si es necesario
    // ... (puedes ajustar la posición o las dimensiones de la caja según lo desees)

    // Renderizar la caja del texto
    SDL_SetRenderDrawColor(renderer.Get(), boxColor.r, boxColor.g, boxColor.b, boxColor.a);
    SDL_RenderFillRect(renderer.Get(), &textBoxRect);

    // Dibujar el texto en las coordenadas calculadas
    renderer.Copy(textTexture, SDL2pp::NullOpt, SDL2pp::Rect(textX, textY, textWidth, textHeight));
}

void TextureManager::drawText(const std::string &text, int x, int y, const std::string &fontPath, int fontSize,
                              SDL_Color textColor, SDL2pp::Renderer &renderer) {
    SDL2pp::Font font(fontPath, fontSize);
    SDL2pp::Texture textTexture(renderer, font.RenderText_Blended(text, textColor));

    int textWidth = textTexture.GetWidth();
    int textHeight = textTexture.GetHeight();

    renderer.Copy(textTexture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, textWidth, textHeight));
}

void TextureManager::setColorMod(const std::string &id, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get();
        if (texture) {
            texture->SetColorMod(r, g, b);
            texture->SetAlphaMod(alpha);
        }
    }
}

void TextureManager::resetColorMod(const std::string &id) {
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get();
        if (texture) {
            texture->SetColorMod(255, 255, 255);
            texture->SetAlphaMod(255);
        }
    }
}
