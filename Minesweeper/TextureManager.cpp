#include "TextureManager.h"

TextureManager::TextureManager() {
    LoadTextures("texture1");
    LoadTextures("texture2");
    // ...
}

void TextureManager::LoadTextures(string name) {
    sf::Texture texture;
    if (!texture.loadFromFile(name)) {
        // Handle error loading texture
    }
    textures.emplace(name, texture);
}

sf::Texture& TextureManager::getTexture(string name) {
    auto found = textures.find(name);
    if (found != textures.end()) {
        return found->second;
    }
    // Handle missing texture
}

void TextureManager::Clear() {
    for (auto& [name, texture] : textures) {
        texture.~Texture();
    }
    textures.clear();
}