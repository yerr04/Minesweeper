#include "TextureManager.h"

sf::Texture& TextureManager::getTexture(std::string name) {
    if (textures.find(name) == textures.end()) {
        LoadTextures(name);
    }
    return textures[name];
}

void TextureManager::LoadTextures(std::string name) {
    sf::Texture texture;
    texture.loadFromFile("./files/images/" + name + ".png");
    textures.emplace(name, texture);
}

void TextureManager::Clear() {
    textures.clear();
}