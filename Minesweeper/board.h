#include <fstream>
#include "Tiles.h"

class Board {
    int rows, cols, mines;
    Tiles** tiles;
    int getMines();

public:
    Board(int rows, int cols, int mines);
    void generateTiles(string board);
    void clear();
    void draw(sf::RenderWindow& window);
    void reveal(int x, int y);
    void flag(int x, int y);
    bool isGameOver();
    bool isGameWon();
    int getRows();
    int getCols();
    int getMines();
    Tiles* getTile(int x, int y);
    ~Board();
};