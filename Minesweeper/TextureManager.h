#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    void LoadTextures(std::string name);
public:
    sf::Texture& getTexture(std::string name);
    void Clear();
};