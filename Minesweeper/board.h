#include "Tiles.h"
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Board {
    std::vector<std::vector<Tiles*>> tiles;
    int mines = 0;
    int minesMax;
    bool isDebug = false;
    bool isPaused = false;
    bool isLeaderboard = false;
    bool isLost = false;
    bool isWon = false;
    int tilesLeft = numRows * numCols;

    sf::Texture digits, debug, happyFace, lostFace, winFace, flag, mine, number1, number2, number3, number4, number5,
        number6, number7, number8, hiddenTile, shownTile, pause, play, leaderboard;

    sf::Sprite faceSprite, debugSprite, scoreSprite1, scoreSprite2, scoreSprite3, pauseSprite, leaderboardSprite;

    std::string score = "000";

public:
    int numRows = 16;
    int numCols = 25;

    // Constructor
    Board();

    // Destructor
    ~Board();

    // getters
    Tiles* getTile(int row, int column);
    void getTextures();

    // setters
    void setNeighbors();

    void setSprite(sf::Sprite* sprite, sf::Texture& text);

    // game stuff
    void drawBoard(sf::RenderWindow& window);

    void updateScore();

    void addScore(int toAdd);

    void generateMines();

    void setup();

    void loadFromFile(std::string fileName);

    void onClick(int x, int y, std::string clickType);

    void Reveal(Tiles* tile);

    void Flag(Tiles* tile);

    void lostGame();
    void winGame();
    void checkWin();

};