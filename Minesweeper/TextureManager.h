#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

class TextureManager {
    static map<string, sf::Texture> textures;
    static void LoadTextures(string name);

public:
    static sf::Texture& getTexture(string name);
    static void Clear();
};