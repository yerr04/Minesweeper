#include <iostream>
#include "Tiles.h"

Tiles::Tiles(sf::Texture& texture, sf::Texture& flagTexture) : texture(texture) {
	initSprite->setTexture(texture);
	nextSprite->setTexture(texture);
	flagSprite->setTexture(flagTexture);
}

// setters
void Tiles::setShown(bool isShown) {
	this->isShown = isShown;
}

void Tiles::setFlag(bool isFlagged) {
	this->isFlagged = isFlagged;
}

void Tiles::setMine(bool isMine) {
	this->isMine = isMine;
}

void Tiles::setNeighbors(std::vector<Tiles*>& adjTiles) {
	neighbors = adjTiles;
	adjMines = 0;
	for (Tiles* tile : neighbors) {
		Tiles* temp = tile;
		if (tile->getIsMine()) {
			adjMines++;
		}
	}
}

// getters
sf::Sprite* Tiles::getInitSprite() {
	return initSprite;
}

sf::Sprite* Tiles::getFlagSprite() {
	return flagSprite;
}

sf::Sprite* Tiles::getNextSprite() {
	return nextSprite;
}

bool Tiles::getIsShown() {
	return isShown;
}

bool Tiles::getIsFlagged() {
	return isFlagged;
}

bool Tiles::getIsMine() {
	return isMine;
}

int Tiles::getAdjMines() {
	return adjMines;
}
std::vector<Tiles*>* Tiles::getNeighbors() {
	return &neighbors;
}

// methods
void Tiles::setpos(int x, int y) {
	initSprite->move(sf::Vector2f(y, x));
	nextSprite->move(sf::Vector2f(y, x));
	flagSprite->move(sf::Vector2f(y, x));
}

void Tiles::createMine() {
	isMine = true;
}
