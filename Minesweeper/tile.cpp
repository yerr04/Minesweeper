#include "tile.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

Tile::Tile() {
    revealed = false;
    hasFlag = false;
    nearbyMines = 0;
    isMine = false;
}

void Tile::reveal() {
    revealed = true;
}

void Tile::flag() {
    hasFlag = true;
}

void Tile::setMine() {
    isMine = true;
}

void Tile::setNeighbors(vector<Tile*> neighbors) {
    this->neighbors = neighbors;
}

void Tile::draw(sf::RenderWindow &window) {
    if (isMine) {
        mine.setTexture(TextureManager::getTexture(3));
        window.draw(mine);
    }
    else if (nearbyMines > 0) {
        number.setTexture(TextureManager::getTexture(nearbyMines));
        window.draw(number);
    }
    else {
        sprite.setTexture(TextureManager::getTexture(1));
        window.draw(sprite);
    }
}

bool Tile::isMine() {
    return isMine;
}

void Tile::setpos(int x, int y) {
    sprite.setPosition(x, y);
    flag.setPosition(x, y);
    number.setPosition(x, y);
    mine.setPosition(x, y);
}