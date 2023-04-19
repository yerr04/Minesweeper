#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using namespace std;

class TextureManager {
    unordered map<string, sf::Texture> textures;
    void LoadTextures(string name);

public:
    sf::Texture& getTexture(string name);
    void Clear();
};