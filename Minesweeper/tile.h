#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Tile {
    bool revealed;
    bool hasFlag;
    int nearbyMines;
    vector<Tile*> neighbors;

    sf::Sprite sprite;
    sf::Sprite flag;
    sf::Sprite number;
    sf::Sprite mine;


public:
    bool isMine;
    // default constructor
    Tile();
    // setters
    void reveal();
    void flag();
    void setMine();
    void setNeighbors(vector<Tile*> neighbors);
    // other functions
    void draw(sf::RenderWindow &window);
    void setpos(int x, int y);
    // getters
    void isMine();
    bool isRevealed();
    bool isFlagged();
    int getNearbyMines();
};
