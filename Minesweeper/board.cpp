#include "Board.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "leaderboard.h"
#include <SFML/Graphics.hpp>
using namespace std;

// Constructor
Board::Board() {

    if (!digits.loadFromFile("./files/images/digits.png"))
        cout << "Error" << endl;
    else if (!debug.loadFromFile("./files/images/debug.png"))
        cout << "Error" << endl;
    else if (!happyFace.loadFromFile("./files/images/face_happy.png"))
        cout << "Error" << endl;
    else if (!lostFace.loadFromFile("./files/images/face_lose.png"))
        cout << "Error" << endl;
    else if (!winFace.loadFromFile("./files/images/face_win.png"))
        cout << "Error" << endl;
    else if (!flag.loadFromFile("./files/images/flag.png"))
        cout << "Error" << endl;
    else if (!mine.loadFromFile("./files/images/mine.png"))
        cout << "Error" << endl;
    else if (!number1.loadFromFile("./files/images/number_1.png"))
        cout << "Error" << endl;
    else if (!number2.loadFromFile("./files/images/number_2.png"))
        cout << "Error" << endl;
    else if (!number3.loadFromFile("./files/images/number_3.png"))
        cout << "Error" << endl;
    else if (!number4.loadFromFile("./files/images/number_4.png"))
        cout << "Error" << endl;
    else if (!number5.loadFromFile("./files/images/number_5.png"))
        cout << "Error" << endl;
    else if (!number6.loadFromFile("./files/images/number_6.png"))
        cout << "Error" << endl;
    else if (!number7.loadFromFile("./files/images/number_7.png"))
        cout << "Error" << endl;
    else if (!number8.loadFromFile("./files/images/number_8.png"))
        cout << "Error" << endl;
    else if (!hiddenTile.loadFromFile("./files/images/tile_hidden.png"))
        cout << "Error" << endl;
    else if (!shownTile.loadFromFile("./files/images/tile_revealed.png"))
        cout << "Error" << endl;
    else if (!pause.loadFromFile("./files/images/pause.png"))
        cout << "Error" << endl;
    else if (!play.loadFromFile("./files/images/play.png"))
        cout << "Error" << endl;
	else if (!leaderboard.loadFromFile("./files/images/leaderboard.png"))
		cout << "Error" << endl;
	else
		cout << "All images loaded successfully" << endl;

    loadFromFile("./files/board_config.cfg");
    cout << numRows << " " << numCols << endl;
    faceSprite.setTexture(happyFace);
    faceSprite.move(sf::Vector2f(((numCols / 2.0) * 32) - 32, 32 * (numRows + 0.5f)));
    debugSprite.setTexture(debug);
    debugSprite.move(sf::Vector2f((numCols * 32) - 304, 32 * (numRows + 0.5f)));
    pauseSprite.setTexture(pause);
    pauseSprite.move(sf::Vector2f((numCols * 32) - 240, 32 * (numRows + 0.5f)));
    leaderboardSprite.setTexture(leaderboard);
    leaderboardSprite.move(sf::Vector2f((numCols * 32) - 176, 32 * (numRows + 0.5f)));
    scoreSprite1.move(sf::Vector2f(12, (32 * (numRows + 0.5f) + 16)));
    scoreSprite1.setTexture(digits);
    scoreSprite2.move(sf::Vector2f(33, (32 * (numRows + 0.5f) + 16)));
    scoreSprite2.setTexture(digits);
    scoreSprite3.move(sf::Vector2f(54, (32 * (numRows + 0.5f) + 16)));
    scoreSprite3.setTexture(digits);
    setup();
}

// Destructor
Board::~Board() {
    for (int i = 0; i < numRows; i++) { // Might Change
        for (int j = 0; j < numCols; j++) { // Might change
            delete tiles[i][j];
        }
    }
}

// Accessors
Tiles* Board::getTile(int row, int column) {
    return tiles[row][column];
}

// Mutators
void Board::setNeighbors() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            vector<Tiles*> neighbors;
            if (i - 1 >= 0) {
                if (j + 1 < numCols) {
                    Tiles* tile = tiles[i - 1][j + 1];
                    neighbors.push_back(tile);
                }
                if (j - 1 >= 0) {
                    Tiles* tile = tiles[i - 1][j - 1];
                    neighbors.push_back(tile);
                }
                Tiles* tile = tiles[i - 1][j];
                neighbors.push_back(tile);
            }
            if (i + 1 < numRows) {
                if (j + 1 < numCols) {
                    Tiles* tile = tiles[i + 1][j + 1];
                    neighbors.push_back(tile);
                }
                if (j - 1 >= 0) {
                    Tiles* tile = tiles[i + 1][j - 1];
                    neighbors.push_back(tile);
                }
                Tiles* tile = tiles[i + 1][j];
                neighbors.push_back(tile);
            }
            if (j + 1 < numCols) {
                Tiles* tile = tiles[i][j + 1];
                neighbors.push_back(tile);
            }
            if (j - 1 >= 0) {
                Tiles* tile = tiles[i][j - 1];
                neighbors.push_back(tile);
            }
            Tiles* temp = tiles[i][j];
            temp->setNeighbors(neighbors);
            if (temp->getIsMine()) {
                setSprite(temp->getNextSprite(), mine);
            }
            else {
                int neighborCount = temp->getAdjMines();
                if (neighborCount == 0) {
                    setSprite(temp->getNextSprite(), shownTile);
                }
                else if (neighborCount == 1) {
                    setSprite(temp->getNextSprite(), number1);
                }
                else if (neighborCount == 2) {
                    setSprite(temp->getNextSprite(), number2);
                }
                else if (neighborCount == 3) {
                    setSprite(temp->getNextSprite(), number3);
                }
                else if (neighborCount == 4) {
                    setSprite(temp->getNextSprite(), number4);
                }
                else if (neighborCount == 5) {
                    setSprite(temp->getNextSprite(), number5);
                }
                else if (neighborCount == 6) {
                    setSprite(temp->getNextSprite(), number6);
                }
                else if (neighborCount == 7) {
                    setSprite(temp->getNextSprite(), number7);
                }
                else if (neighborCount == 8) {
                    setSprite(temp->getNextSprite(), number8);
                }
            }
        }
    }
}

void Board::setSprite(sf::Sprite* sprite, sf::Texture& text) {
    sprite->setTexture(text);
}

// Functions

void Board::drawBoard(sf::RenderWindow& window) {
    for (int i = 0; i < numRows; i++) { // Might Change
        for (int j = 0; j < numCols; j++) { // Might Change
            Tiles* tile = tiles[i][j];
            sf::Sprite* sprite = tile->getInitSprite();
            sf::Sprite* sprite2 = tile->getNextSprite();

            if (isLost) {
                if (tile->getIsShown()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                }
                else {
                    if (tile->getIsMine()) {
                        setSprite(sprite, shownTile);
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    }
                    else {
                        window.draw(*sprite);
                    }
                }
            }
            else if (isWon) {
                if (tile->getIsShown()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                }
                else {
                    if (tile->getIsMine()) {
                        window.draw(*sprite);
                        window.draw(*tile->getFlagSprite());
                    }
                }
            }
            else {
                if (isDebug) {
                    window.draw(*sprite);
                    if (tile->getIsMine() || tile->getIsShown()) {
                        window.draw(*sprite2);
                    }
                    if (tile->getIsFlagged() && !tile->getIsShown()) {
                        window.draw(*tile->getFlagSprite());
                    }
                }
                else {
                    if (tile->getIsShown()) {
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    }
                    else {
                        window.draw(*sprite);
                        if (tile->getIsShown()) {
                            window.draw(*tile->getFlagSprite());
                        }
                    }
                }
            }
            if (tile->getIsFlagged() && !tile->getIsShown()) {
				window.draw(*tile->getFlagSprite());
			}
            if (isPaused) {
                setSprite(sprite, shownTile);
                window.draw(*sprite);
            }
            if (!isPaused) {
                if (!tile->getIsShown()) {
					setSprite(sprite, hiddenTile);
				}
            }
            if (tile->getIsFlagged() && !tile->getIsShown()) {
                window.draw(*tile->getFlagSprite());
            }
        }
    }
    updateScore();
    window.draw(faceSprite);
    window.draw(debugSprite);
    window.draw(pauseSprite);
    window.draw(leaderboardSprite);
    window.draw(scoreSprite1);
    window.draw(scoreSprite2);
    window.draw(scoreSprite3);
}

void Board::updateScore() {
    int flagged = 0;
    for (int i = 0; i < numRows; i++) { // Might change
        for (int j = 0; j < numCols; j++) {
            Tiles* temp = tiles[i][j];
            if (temp->getIsFlagged()) {
                flagged++;
            }
        }
    }

    int tempScore = mines - flagged;
    score = to_string(tempScore) + "";
    char hundreds = score[0];
    if (hundreds == '-') {
        scoreSprite1.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
    }
    else {
        int first = hundreds - 48;
        scoreSprite1.setTextureRect(sf::IntRect(21 * first, 0, 21, 32));
    }
    char tens = score[1];
    int second = tens - 48;
    scoreSprite2.setTextureRect(sf::IntRect(21 * second, 0, 21, 32));
    char ones = score[2];
    int third = ones - 48;
    scoreSprite3.setTextureRect(sf::IntRect(21 * third, 0, 21, 32));
}

void Board::addScore(int toAdd) {
    int tempScore = stoi(score);
    tempScore += toAdd;
    score = "" + to_string(tempScore);
}

void Board::generateMines() {
    srand(time(nullptr));
    while (mines < minesMax) {
        int i = rand() % numRows; // Might change
        int j = rand() % numCols; // Might change
        Tiles* tile = tiles[i][j];
        if (!tile->getIsMine()) {
            tile->createMine();
            setSprite(tile->getNextSprite(), mine);
            mines++;
            remainingTiles--;
        }
    }
}

void Board::setup() {
    isLost = false;
    isWon = false;
    remainingTiles = numRows * numCols; // Might change
    setSprite(&faceSprite, happyFace);
    loadFromFile("./files/board_config.cfg");
    mines = 0;
    generateMines();
    setNeighbors();
}

void Board::loadFromFile(string fileName) {
    // read numCols and numRows from .cfg file
    ifstream file(fileName);
    string line;
    getline(file, line);
    numCols = stoi(line);
    getline(file, line);
    numRows = stoi(line);
    getline(file, line);
    minesMax = stoi(line);

    // add tiles to board
    tiles.resize(numRows);
    for (int i = 0; i < numRows; i++) {
		tiles[i].resize(numCols);
	}
    for (int i = 0; i < numRows; i++) { // Might change
    		for (int j = 0; j < numCols; j++) { // Might change
                if (!tiles[i][j]) {
				delete tiles[i][j];
			}
            			tiles[i][j] = new Tiles(hiddenTile, flag);
            			tiles[i][j]->setpos(i * 32, j * 32);
            		}
    	}
    generateMines();
    setNeighbors();
}

void Board::onClick(int x, int y, string clickType) {
    if (y > (32 * (numRows + 0.5f)) && y < (32 * (numRows + 0.5f) + 66)) {
        if (x >= (((numCols / 2.0) * 32) - 32) && x <= (((numCols / 2.0) * 32) + 34)) {
            setup();
        }
        else if (x >= ((numCols * 32) - 304) && x < ((numCols * 32) - 238) && !isLost && !isWon) {
            if (isDebug) {
                isDebug = false;
            }
            else {
                isDebug = true;
            }
        }
        else if (x >= ((numCols * 32) - 240) && x < ((numCols * 32) - 174) && !isLost && !isWon) {
            if (isPaused) {
                isPaused = false;
                setSprite(&pauseSprite, pause);
            }
            else {
				isPaused = true;
                setSprite(&pauseSprite, play);
                
			}
		}
        else if (x >= ((numCols * 32) - 176) && x < ((numCols * 32) - 110) && !isLost && !isWon) {
            if (!isLeaderboard) {
                Leaderboard((16 * numCols), (numRows * 16) + 50);
                isLeaderboard = false;
            
            }
		}
    }
    else if (!isLost && !isWon) {
        int row = y / 32;
        int column = x / 32;
        Tiles* temp = tiles[row][column];
        if (clickType == "left" && !isPaused) {
            if (!temp->getIsFlagged() && !temp->getIsShown()) {
                onReveal(temp);
            }
        }
        else if (clickType == "right" && !isPaused) {
            toggleFlag(temp);
        }
    }
}

void Board::onReveal(Tiles* tile) {
    tile->setShown(true);
    setSprite(tile->getInitSprite(), shownTile);
    if (tile->getIsMine()) {
        endGame();
    }
    else {
        remainingTiles--;
        if (remainingTiles <= 0) {
            winGame();
        }
        if (tile->getAdjMines() == 0) {
            vector<Tiles*>* neighbors = tile->getNeighbors();
            int size = neighbors->size();
            for (int i = 0; i < size; i++) {
                Tiles* neighbor = neighbors->at(i);
                if (!neighbor->getIsShown()) {
                    onReveal(neighbor);
                }
            }
        }
    }
}

void Board::toggleFlag(Tiles* tile) {
    if (tile->getIsFlagged()) {
        tile->setFlag(false);
    }
    else {
        tile->setFlag(true);
    }
}

void Board::endGame() {
    isLost = true;
    isDebug = false;
    setSprite(&faceSprite, lostFace);
}

void Board::winGame() {
    isWon = true;
    isDebug = false;
    setSprite(&faceSprite, winFace);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Tiles* tile = tiles[i][j];

            if (tile->getIsShown()) {
                tile->setFlag(false);
            }
            else {
                tile->setFlag(true);
            }
        }
    }
}