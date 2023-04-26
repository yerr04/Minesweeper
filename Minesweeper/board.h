#include "Tiles.h"
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Board {

    Tiles* tiles[16][25];
    int mines = 0;
    bool isDebug = false;
    bool isPaused = false;
    bool isLeaderboard = false;
    bool isLost = false;
    bool isWon = false;
    int remainingTiles = 400;
    TextureManager textureManager;

    sf::Texture digits, debug, happyFace, lostFace, winFace, flag, mine, number1, number2, number3, number4, number5,
        number6, number7, number8, hiddenTile, shownTile, pause, play, leaderboard;

    sf::Sprite faceSprite, debugSprite, scoreSprite1, scoreSprite2, scoreSprite3, pauseSprite, playSprite, leaderboardSprite;

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

    void generateMines();

    void setup();

    void loadFromFile(std::string fileName);

    void onClick(int x, int y, std::string clickType);

    void onReveal(Tiles* tile);

    void toggleFlag(Tiles* tile);

    void endGame();
    void winGame();

};