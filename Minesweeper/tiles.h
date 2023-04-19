#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"

using namespace std;

class Tiles{
    private:
        int x, y, adjmines;
        bool isMine, isFlagged, isRevealed;
        sf::Texture number;
        sf::Texture sprite;
        sf::Texture flagged;
        sf::Texture mine;
        vector<Tiles*> neighbors;

    public:
        Tiles();
        Tiles(int x, int y, bool isMine);
        void setNeighbors(vector<Tiles*> neighbors, int x, int y);
        void setAdjMines();
        void setRevealed();
        void setFlagged();
        void setMine();
        void setNumber();
        void setSprite();
        void setpos(int x, int y);
        void draw(sf::RenderWindow& window);
        int getX();
        int getY();
        int getAdjMines();
        bool getIsMine();
        bool getIsFlagged();
        bool getIsRevealed();
        vector<Tiles*> getNeighbors();

}