#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTextures(string name) {
    sf::Texture texture;
    texture.loadFromFile(name);
    textures[name] = texture;
}

sf::Texture& TextureManager::getTexture(string name) {
    if (textures.find(name) == textures.end()) {
        LoadTextures(name);
    }
    return textures[name];
}

void TextureManager::Clear() {
    textures.clear();
}


