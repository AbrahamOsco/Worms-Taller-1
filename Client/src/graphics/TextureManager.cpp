//
// Created by riclui on 25/10/23.
//

#include <utility>
#include "TextureManager.h"

void TextureManager::load(const std::string &fileName, std::string &id, SDL2pp::Renderer &renderer) {
    try {
        SDL2pp::Surface surface(fileName);
        std::unique_ptr<SDL2pp::Texture> texture = std::make_unique<SDL2pp::Texture>(renderer, surface);
        m_textureMap[id] = std::move(texture);
    } catch (const SDL2pp::Exception &ex) {
        std::cerr << "Error al cargar la textura" << std::endl;
    }
}

void TextureManager::draw(const std::string &id, int x, int y, int width, int height, SDL2pp::Renderer &renderer,
                          SDL_RendererFlip flip) {
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get();
        if (texture) {
            SDL2pp::Rect srcRect(0, 0, width, height);
            SDL2pp::Rect destRect(x, y, width, height);
            renderer.Copy(*texture, srcRect, destRect, 0.0, SDL2pp::NullOpt, flip);
        }
    }
}

void
TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentCol,
                          SDL2pp::Renderer &renderer, SDL_RendererFlip flip) {
    auto it = m_textureMap.find(id);
    if (it != m_textureMap.end()) {
        SDL2pp::Texture *texture = it->second.get();
        if (texture) {
            SDL2pp::Rect srcRect(currentCol * width, currentRow * height, width, height);
            SDL2pp::Rect destRect(x, y, width, height);
            renderer.Copy(*texture, srcRect, destRect, 0.0, SDL2pp::NullOpt, flip);
        }
    }
}

void TextureManager::parseTexture(const std::string &yamlFileName, SDL2pp::Renderer &renderer) {
    try {
        // Cargar el archivo YAML
        YAML::Node config = YAML::LoadFile(yamlFileName);
        const YAML::Node &textures = config["textures"];
        for (const YAML::Node &texture : textures) {
            std::string name = texture["name"].as<std::string>();
            std::string source = texture["source"].as<std::string>();
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
    int textX = x;
    int textY = y;

    int padding = 2;
    SDL_Rect textBoxRect = {x - padding, y - padding, textWidth + 2 * padding, textHeight + 2 * padding};
    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer.Get(), boxColor.r, boxColor.g, boxColor.b, boxColor.a);
    SDL_RenderFillRect(renderer.Get(), &textBoxRect);
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
