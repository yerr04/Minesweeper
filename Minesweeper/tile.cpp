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

    sprite.setTexture(Textures::getTexture("tile"));
    flag.setTexture(Textures::getTexture("flag"));
    mine.setTexture(Textures::getTexture("mine"));
}

// getters
bool Tile::isRevealed() {
    return revealed;
}

bool Tile::isFlagged() {
    return hasFlag;
}

int Tile::getNearbyMines() {
    return nearbyMines;
}

// setters
void Tile::setMine() {
    isMine = true;
}

void Tile::setNeighbors(vector<Tile*> neighbors) {
    this->neighbors = neighbors;
}

// other functions   
void Tile::reveal() {
    if (revealed) return;
    revealed = true;
    sprite.setTexture(Textures::getTexture("tile_revealed"));
    if (isMine) return;
    for (Tile* neighbor : neighbors) {
        if (!neighbor->isMine) neighbor->reveal();
    }
}

void Tile::flag() {
    if (revealed) return;
    hasFlag = !hasFlag;
}

void Tile::draw(sf::RenderWindow &window) {
    if (revealed) {
        if (isMine) {
            window.draw(mine);
        } else {
            window.draw(number);
        }
    } else {
        window.draw(sprite);
        if (hasFlag) {
            window.draw(flag);
        }
    }
}
