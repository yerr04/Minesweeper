#include <fstream>
#include "board.h"

TextureManager textureManager;

Board::Board() {
	std::ifstream file("./files/board_config.cfg");
	std::string line;
	rows = getline(file, line) ? std::stoi(line) : 10;
	cols = getline(file, line) ? std::stoi(line) : 10;
	mines = getline(file, line) ? std::stoi(line) : 10;
	TextureManager textureManager;

	for (int i = 0; i < rows; i++) {
		std::vector<Tiles*> row;
		for (int j = 0; j < cols; j++) {
			row.push_back(new Tiles(textureManager.getTexture("tile_hidden"), textureManager.getTexture("flag")));
		}
		tiles.push_back(row);
	}
}

Board::Board(int rows, int cols, int mines) {
	this->rows = rows;
	this->cols = cols;
	this->mines = mines;
	TextureManager textureManager;
	for (int i = 0; i < rows; i++) {
		std::vector<Tiles*> row;
		for (int j = 0; j < cols; j++) {
			row.push_back(new Tiles(textureManager.getTexture("tile_hidden"), textureManager.getTexture("flag")));
		}
		tiles.push_back(row);
	}
}

Board::~Board() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			delete tiles[i][j];
		}
	}
}

void Board::loadFromFile(std::string file) {
	std::ifstream fileStream(file);
	std::string line;
	rows = getline(fileStream, line) ? std::stoi(line) : 10;
	cols = getline(fileStream, line) ? std::stoi(line) : 10;
	mines = getline(fileStream, line) ? std::stoi(line) : 10;
	for (int i = 0; i < rows; i++) {
		std::vector<Tiles*> row;
		for (int j = 0; j < cols; j++) {
			row.push_back(new Tiles(textureManager.getTexture("tile_hidden"), textureManager.getTexture("flag")));
		}
		tiles.push_back(row);
	}
}

void Board::setSprite(sf::Sprite* sprite, sf::Texture& texture) {
	sprite->setTexture(texture);
}

void Board::setNeighbors() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::vector<Tiles*> neighbors;
			if (i > 0) {
				neighbors.push_back(tiles[i - 1][j]);
				if (j > 0) {
					neighbors.push_back(tiles[i - 1][j - 1]);
				}
				if (j < cols - 1) {
					neighbors.push_back(tiles[i - 1][j + 1]);
				}
			}
			if (i < rows - 1) {
				neighbors.push_back(tiles[i + 1][j]);
				if (j > 0) {
					neighbors.push_back(tiles[i + 1][j - 1]);
				}
				if (j < cols - 1) {
					neighbors.push_back(tiles[i + 1][j + 1]);
				}
			}
			if (j > 0) {
				neighbors.push_back(tiles[i][j - 1]);
			}
			if (j < cols - 1) {
				neighbors.push_back(tiles[i][j + 1]);
			}
			tiles[i][j]->setNeighbors(neighbors);
		}
	}
}

void Board::generateMines() {
	int minesPlaced = 0;
	while (minesPlaced < mines) {
		int x = rand() % rows;
		int y = rand() % cols;
		Tiles* tile = tiles[x][y];
		
		if (!tile->getIsMine()) {
			tile->getIsMine();
			setSprite(tile->getSprite(), textureManager.getTexture("mine"));
			mines++;
			remainingTiles--;
		}
	}
}

void Board::onClick(int x, int y, std::string click) {
	Tiles* tile = tiles[x][y];
	if (click == "left") {
		if (!tile->getIsFlagged()) {
			if (tile->getIsMine()) {
				endGame();
			}
			else {
				reveal(x, y);
			}
		}
	}
	else if (click == "right") {
		flag(tile);
	}
}



