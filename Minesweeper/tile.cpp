#include "tile.h"
#include <iostream>
#include <string>

Tile::Tile() {
       tile->setTexture(texture);
       sprite->setTexture(texture);
       flagged->setTexture(flagTexture);

}

// Getters
Sprite* 