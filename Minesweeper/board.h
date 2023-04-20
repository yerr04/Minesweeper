#include <SFML/Graphics.hpp>
#include "Tiles.h"
#include "TextureManager.h"
#include <string>
#include <fstream>

class Board {
	std::vector<std::vector<Tiles*>> tiles;
	int rows, cols, mines;
	bool debug, isGameOver, won;
	int remainingTiles;

	std::string score = "000";

public:
	Board();
	Board(int rows, int cols, int mines);
	~Board();
	Tiles* getTile(int x, int y);
	void setSprite(sf::Sprite* sprite, sf::Texture& texture);
	void setNeighbors();

	void draw(sf::RenderWindow& window);
	void update();
	void generateMines();
	void reveal(int x, int y);
	void loadFromFile(std::string filename);
	void onClick(int x, int y, std::string click);
	void flag(Tiles* tile);
	void endGame();
	void wingame();
};