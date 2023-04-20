#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using namespace std;

class TextureManager {
public:
    TextureManager();
    sf::Texture& getTexture(string name);
    void Clear();

private:
    unordered_map<string, sf::Texture> textures;
    void LoadTextures(string name);
};