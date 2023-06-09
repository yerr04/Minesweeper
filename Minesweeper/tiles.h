#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Tiles {
	bool isShown = false;
	bool isFlagged = false;
	bool isMine = false;
	int adjMines = 0;
	std::vector<Tiles*> neighbors;
	sf::Sprite* initSprite = new sf::Sprite;
	sf::Sprite* nextSprite = new sf::Sprite;
	sf::Sprite* flagSprite = new sf::Sprite;
	sf::Texture& texture;
public:
	// constructor
	Tiles(sf::Texture& texture, sf::Texture& flagTexture);

	//setters
	void setShown(bool isShown);
	void setFlag(bool isFlagged);
	void setMine(bool isMine);
	void setNeighbors(std::vector<Tiles*>& adjTiles);

	// methods
	void setpos(int x, int y);
	void createMine();

	// getters
	sf::Sprite* getInitSprite();
	sf::Sprite* getFlagSprite();
	sf::Sprite* getNextSprite();
	bool getIsShown();
	bool getIsFlagged();
	bool getIsMine();
	int getAdjMines();
	std:: vector<Tiles*>* getNeighbors();
};