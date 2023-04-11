#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Tile {
    bool isRevealed;
    bool isFlagged;
    bool isMine;
    int nearbyMines;
    vector<Tile*> neighbors;

    sf::Sprite* tile = new sf::Sprite;
    sf::Sprite* sprite = new sf::Sprite;
    sf::Sprite* flagged = new sf::Sprite;


public:
    Tile();
    Tile(Texture* texture, Texture* flagged);
    ~Tile();

    // Getters
    sf::Sprite* getHidden();
    sf::Sprite* getRevealed();
    sf::Sprite* getFlagged();

    bool getIsRevealed();
    bool getIsFlagged();
    bool getIsMine();
    int getNearbyMines();
    vector<Tile*> getNeighbors();

    // Setters
    void setIsRevealed(bool isRevealed);
    void setIsFlagged(bool isFlagged);
    void setIsMine(bool isMine);
    void setNearbyMines(int nearbyMines);
    void setNeighbors(vector<Tile*> neighbors);

    // Other methods
    void move(float x, float y);
    void createMine();
    void draw(sf::RenderWindow& window);
    
}