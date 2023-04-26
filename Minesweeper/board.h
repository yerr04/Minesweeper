#include "Tiles.h"
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Board {

    Tiles* tiles[16][25];
    int bombs = 0;
    bool isDebug = false;
    bool isLost = false;
    bool isWon = false;
    int remainingTiles = 400;
    TextureManager textureManager;

    sf::Texture digits, debug, happyFace, lostFace, winFace, flag, bomb, number1, number2, number3, number4, number5,
        number6, number7, number8, test1, test2, test3, hiddenTile, shownTile;

    sf::Sprite faceSprite, debugSprite, test1_sprite, test2_sprite, test3_sprite, scoreSprite1, scoreSprite2, scoreSprite3;

    std::string score = "000";

public:
    // Constructor
    Board();

    // Destructor
    ~Board();

    // Accessors
    Tiles* getTile(int row, int column);

    // Mutators
    void setNeighbors();

    void setSprite(sf::Sprite* sprite, sf::Texture& text);

    // Functions
    void drawBoard(sf::RenderWindow& window);

    void updateScore();

    void addScore(int toAdd);

    void generateBombs();

    void setup();

    void loadFromFile(std::string fileName);

    void onClick(int x, int y, std::string clickType);

    void onReveal(Tiles* tile);

    void toggleFlag(Tiles* tile);

    void endGame();
    void winGame();

};