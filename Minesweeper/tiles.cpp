#include "tiles.h"

Tiles::Tiles() {
    x = 0;
    y = 0;
    adjmines = 0;
    isMine = false;
    isFlagged = false;
    isRevealed = false;
    sprite.setTexture(TextureManager::getTexture("./files/images/tile_hidden.png"));
    flagged.setTexture(TextureManager::getTexture("./files/images/flag.png"));
    mine.setTexture(TextureManager::getTexture("./files/images/mine.png"));
}

Tiles::Tiles(int x, int y, bool isMine) {
    this->x = x;
    this->y = y;
    this->isMine = isMine;
    adjmines = 0;
    isFlagged = false;
    isRevealed = false;
}

void Tiles::setNeighbors(vector<Tiles*> neighbors, int x, int y) {
    if (x > 0)
    {
        this->neighbors.push_back(neighbors[x - 1 + y * 10]);
        if (y > 0)
        {
            this->neighbors.push_back(neighbors[x - 1 + (y - 1) * 10]);
        }
        if (y < 9)
        {
            this->neighbors.push_back(neighbors[x - 1 + (y + 1) * 10]);
        }
            switch(adjmines){
        case 0:
            sprite.setTexture(TextureManager::getTexture("./files/images/tile_revealed.png"));
            break;
        case 1:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_1.png"));
            break;
        case 2:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_2.png"));
            break;
        case 3:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_3.png"));
            break;
        case 4:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_4.png"));
            break;
        case 5:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_5.png"));
            break;
        case 6:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_6.png"));
            break;
        case 7:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_7.png"));
            break;
        case 8:
            sprite.setTexture(TextureManager::getTexture("./files/images/number_8.png"));
            break;
    }
    }
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