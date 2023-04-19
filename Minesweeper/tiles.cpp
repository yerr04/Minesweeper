#include "tiles.h"

Tiles::Tiles() {
    x = 0;
    y = 0;
    adjmines = 0;
    isMine = false;
    isFlagged = false;
    isRevealed = false;
}

Tiles::Tiles(int x, int y, bool isMine) {
    this->x = x;
    this->y = y;
    this->isMine = isMine;
    adjmines = 0;
    isFlagged = false;
    isRevealed = false;
}

void Tiles::setNeighbors(vector<Tiles*> neighbors) {
    this->neighbors = neighbors;
}

void Tiles::setAdjMines() {
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors[i]->getIsMine()) {
            adjmines++;
        }
    }
}

void Tiles::setRevealed() {
    isRevealed = true;
}

void Tiles::setFlagged() {
    isFlagged = true;
}

void Tiles::setMine() {
    isMine = true;
}

void Tiles::setNumber() {
    number = TextureManager::getTexture("./files/images/number_" + to_string(adjmines) + ".png");
}

void Tiles::setSprite() {
    if (isMine) {
        sprite = TextureManager::getTexture("./files/images/mine.png");
    }
    else if (adjmines == 0) {
        sprite = TextureManager::getTexture("./files/images/tile_revealed.png");
    }
    else {
        sprite = TextureManager::getTexture("./files/images/tile_revealed.png");
    }
}

void Tiles::setpos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Tiles::draw(sf::RenderWindow& window) {
    sf::Sprite sprite;
    sprite.setTexture(this->sprite);
    sprite.setPosition(x, y);
    window.draw(sprite);
    if (isRevealed && adjmines > 0) {
        sf::Sprite number;
        number.setTexture(this->number);
        number.setPosition(x, y);
        window.draw(number);
    }
    else if (isFlagged) {
        sf::Sprite flagged;
        flagged.setTexture(TextureManager::getTexture("./files/images/flag.png"));
        flagged.setPosition(x, y);
        window.draw(flagged);
    }
}

int Tiles::getX() {
    return x;
}

int Tiles::getY() {
    return y;
}

int Tiles::getAdjMines() {
    return adjmines;
}

bool Tiles::getIsMine() {
    return isMine;
}

bool Tiles::getIsFlagged() {
    return isFlagged;
}

bool Tiles::getIsRevealed() {
    return isRevealed;
}

vector<Tiles*> Tiles::getNeighbors() {
    return neighbors;
}