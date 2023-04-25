#include "Tiles.h"
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Board {
	int rows;
	int cols;
	int mines;

	sf::RenderWindow* window;
	TextureManager textureManager;
	std::vector<std::vector<Tiles>> tiles;
	public:
		Board(sf::RenderWindow& window);
		Board(sf::RenderWindow& window, int rows, int cols, int mines);
		~Board();
		Tiles* getTile(int row, int col);
		void loadFromFile(std::string file);
		void setSprite(sf::Sprite* sprite, TextureManager& texture);
		void setNeighbors();
		void generateMines();
		void drawBoard();
		void endGame();
		void winGame();
		void toggleFlag(Tiles* tile);
		void revealTile(Tiles* tile);
		void click(int x, int y, std::string type);

};