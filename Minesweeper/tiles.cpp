#include <iostream>
#include "Tiles.h"

Tiles::Tiles(sf::Texture& texture, sf::Texture& flagTexture) : texture(texture) {
	sprite->setTexture(texture);
	sprite2->setTexture(texture);
	flagSprite->setTexture(flagTexture);
}

sf::Sprite* Tiles::getSprite() {
	return sprite;
}

sf::Sprite* Tiles::getFlagSprite() {
	return flagSprite;
}

sf::Sprite* Tiles::getSprite2() {
	return sprite2;
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

void Tiles::setIsShown(bool isShown) {
	this->isShown = isShown;
}

void Tiles::setIsFlagged(bool isFlagged) {
	this->isFlagged = isFlagged;
}

void Tiles::setIsMine(bool isMine) {
	this->isMine = isMine;
}

void Tiles::setNeighbors(std::vector<Tiles*> &neighborTiles) {
	this->neighbors = neighborTiles;
	adjMines = 0;

	for (int i = 0; i < neighbors.size(); i++) {
		Tiles* current = neighbors.at(i);
		if (neighbors[i]->getIsMine()) {
			adjMines++;
		}
	}
}

void Tiles::setpos(int x, int y) {
	sprite->setPosition(x, y);
	sprite2->setPosition(x, y);
	flagSprite->setPosition(x, y);
}

void Tiles::createMine() {
	isMine = true;
}