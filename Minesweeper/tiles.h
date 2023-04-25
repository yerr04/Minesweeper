#include <string>
#include <vector>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class Tiles {
	bool isShown, isFlagged, isMine;
	int adjMines;
	std::vector<Tiles*> neighbors;
	sf::Sprite* sprite;
	sf::Sprite* sprite2;
	sf::Sprite* flagSprite;
	sf::Texture& texture;
public:
	Tiles(sf::Texture& texture, sf::Texture& flagTexture);
	sf::Sprite* getSprite();
	sf::Sprite* getFlagSprite();
	sf::Sprite* getSprite2();
	bool getIsShown();
	bool getIsFlagged();
	bool getIsMine();
	int getAdjMines();
	void setIsShown(bool isShown);
	void setIsFlagged(bool isFlagged);
	void setIsMine(bool isMine);
	void setNeighbors(std::vector<Tiles*> &adjTiles);

	void setpos(int x, int y);
	void createMine();
};