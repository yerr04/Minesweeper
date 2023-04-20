#include <iostream>
#include "board.h"

int Board::getMines() {
    int mines = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (tiles[i][j].getIsMine()) {
                mines++;
            }
        }
    }
    return mines;
}

Board::Board(int rows, int cols, int mines) {
    this->rows = rows;
    this->cols = cols;
    this->mines = mines;
    tiles = new Tiles * [rows];
    for (int i = 0; i < rows; i++) {
        tiles[i] = new Tiles[cols];
    }
    generateTiles();
}

void Board::generateTiles(string board) {
    ifstream file;
    file.open(board);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                char c;
                file >> c;
                if (c == '1') {
                    tiles[i][j] = Tiles(i, j, true);
                }
                else {
                    tiles[i][j] = Tiles(i, j, false);
                }
            }
        }
    }
    file.close();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            vector<Tiles*> neighbors;
            if (i > 0) {
                neighbors.push_back(&tiles[i - 1][j]);
            }
            if (i < rows - 1) {
                neighbors.push_back(&tiles[i + 1][j]);
            }
            if (j > 0) {
                neighbors.push_back(&tiles[i][j - 1]);
            }
            if (j < cols - 1) {
                neighbors.push_back(&tiles[i][j + 1]);
            }
            if (i > 0 && j > 0) {
                neighbors.push_back(&tiles[i - 1][j - 1]);
            }
            if (i > 0 && j < cols - 1) {
                neighbors.push_back(&tiles[i - 1][j + 1]);
            }
            if (i < rows - 1 && j > 0) {
                neighbors.push_back(&tiles[i + 1][j - 1]);
            }
            if (i < rows - 1 && j < cols - 1) {
                neighbors.push_back(&tiles[i + 1][j + 1]);
            }
            tiles[i][j].setNeighbors(neighbors, i, j);
            tiles[i][j].setAdjMines();
            tiles[i][j].setSprite();
        }
    }
}

void Board::clear() {
    for (int i = 0; i < rows; i++) {
        delete tiles[i];
        }
    delete[] tiles;
}

void Board::draw(sf::RenderWindow& window) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tiles[i][j].draw(window);
        }
    }
}

void Board::reveal(int x, int y) {
    if (tiles[x][y].getIsMine()) {
        tiles[x][y].setRevealed();
        return;
    }
    if (tiles[x][y].getIsRevealed()) {
        return;
    }
    tiles[x][y].setRevealed();
    if (tiles[x][y].getAdjMines() == 0) {
        vector<Tiles*> neighbors = tiles[x][y].getNeighbors();
        for (int i = 0; i < neighbors.size(); i++) {
            reveal(neighbors[i]->getX(), neighbors[i]->getY());
        }
    }
}

bool Board::isGameOver() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (tiles[i][j].getIsMine() && tiles[i][j].getIsRevealed()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isGameWon() {
    int revealed = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (tiles[i][j].getIsRevealed()) {
                revealed++;
            }
        }
    }
    if (revealed == rows * cols - mines) {
        return true;
    }
    return false;
}

void Board::flag(int x, int y) {
    tiles[x][y].setFlagged();
}

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

Tiles* Board::getTile(int x, int y) {
    return &tiles[x][y];
}

Board::~Board() {
    clear();
}