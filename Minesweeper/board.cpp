#include "Board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

// Constructor
Board::Board() {

    if (!digits.loadFromFile("../images/digits.png"))
        cout << "Error" << endl;
    else if (!debug.loadFromFile("../images/debug.png"))
        cout << "Error" << endl;
    else if (!happyFace.loadFromFile("../images/face_happy.png"))
        cout << "Error" << endl;
    else if (!lostFace.loadFromFile("../images/face_lose.png"))
        cout << "Error" << endl;
    else if (!winFace.loadFromFile("../images/face_win.png"))
        cout << "Error" << endl;
    else if (!flag.loadFromFile("../images/flag.png"))
        cout << "Error" << endl;
    else if (!bomb.loadFromFile("../images/mine.png"))
        cout << "Error" << endl;
    else if (!number1.loadFromFile("../images/number_1.png"))
        cout << "Error" << endl;
    else if (!number2.loadFromFile("../images/number_2.png"))
        cout << "Error" << endl;
    else if (!number3.loadFromFile("../images/number_3.png"))
        cout << "Error" << endl;
    else if (!number4.loadFromFile("../images/number_4.png"))
        cout << "Error" << endl;
    else if (!number5.loadFromFile("../images/number_5.png"))
        cout << "Error" << endl;
    else if (!number6.loadFromFile("../images/number_6.png"))
        cout << "Error" << endl;
    else if (!number7.loadFromFile("../images/number_7.png"))
        cout << "Error" << endl;
    else if (!number8.loadFromFile("../images/number_8.png"))
        cout << "Error" << endl;
    else if (!test1.loadFromFile("../images/test_1.png"))
        cout << "Error" << endl;
    else if (!test2.loadFromFile("../images/test_2.png"))
        cout << "Error" << endl;
    else if (!test3.loadFromFile("../images/Test_3.png"))
        cout << "Error" << endl;
    else if (!hiddenTile.loadFromFile("../images/tile_hidden.png"))
        cout << "Error" << endl;
    else if (!shownTile.loadFromFile("../images/tile_revealed.png"))
        cout << "Error" << endl;




    faceSprite.setTexture(happyFace);
    faceSprite.move(Vector2f(6 * 64, 32 * 16));
    debugSprite.setTexture(debug);
    debugSprite.move(Vector2f(8 * 64, 32 * 16));
    test1_sprite.setTexture(test1);
    test1_sprite.move(Vector2f(9 * 64, 32 * 16));
    test2_sprite.setTexture(test2);
    test2_sprite.move(Vector2f(10 * 64, 32 * 16));
    test3_sprite.setTexture(test3);
    test3_sprite.move(Vector2f(11 * 64, 32 * 16));
    scoreSprite1.move(Vector2f(0, 32 * 16));
    scoreSprite1.setTexture(digits);
    scoreSprite2.move(Vector2f(21, 32 * 16));
    scoreSprite2.setTexture(digits);
    scoreSprite3.move(Vector2f(42, 32 * 16));
    scoreSprite3.setTexture(digits);
    setup();
}

// Destructor
Board::~Board() {
    for (int i = 0; i < 16; i++) { // Might Change
        for (int j = 0; j < 25; j++) { // Might change
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
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            vector<Tiles*> neighbors;
            if (i - 1 >= 0) {
                if (j + 1 < 25) {
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
            if (i + 1 < 16) {
                if (j + 1 < 25) {
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
            if (j + 1 < 25) {
                Tiles* tile = tiles[i][j + 1];
                neighbors.push_back(tile);
            }
            if (j - 1 >= 0) {
                Tiles* tile = tiles[i][j - 1];
                neighbors.push_back(tile);
            }
            Tiles* current = tiles[i][j];
            current->setNeighbors(neighbors);
            if (current->getIsMine()) {
                setSprite(current->getNextSprite(), bomb);
            }
            else {
                int neighborCount = current->getAdjMines();
                if (neighborCount == 0) {
                    setSprite(current->getNextSprite(), shownTile);
                }
                else if (neighborCount == 1) {
                    setSprite(current->getNextSprite(), number1);
                }
                else if (neighborCount == 2) {
                    setSprite(current->getNextSprite(), number2);
                }
                else if (neighborCount == 3) {
                    setSprite(current->getNextSprite(), number3);
                }
                else if (neighborCount == 4) {
                    setSprite(current->getNextSprite(), number4);
                }
                else if (neighborCount == 5) {
                    setSprite(current->getNextSprite(), number5);
                }
                else if (neighborCount == 6) {
                    setSprite(current->getNextSprite(), number6);
                }
                else if (neighborCount == 7) {
                    setSprite(current->getNextSprite(), number7);
                }
                else if (neighborCount == 8) {
                    setSprite(current->getNextSprite(), number8);
                }
            }
        }
    }
}

void Board::setSprite(sf::Sprite* sprite, sf::Texture& text) {
    sprite->setTexture(text);
}

// Functions

void Board::drawBoard(RenderWindow& window) {
    for (int i = 0; i < 16; i++) { // Might Change
        for (int j = 0; j < 25; j++) { // Might Change
            Tiles* tile = tiles[i][j];
            Sprite* sprite = tile->getInitSprite();
            Sprite* sprite2 = tile->getNextSprite();

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
        }
    }
    updateScore();
    window.draw(faceSprite);
    window.draw(debugSprite);
    window.draw(test1_sprite);;
    window.draw(test2_sprite);
    window.draw(test3_sprite);
    window.draw(scoreSprite1);
    window.draw(scoreSprite2);
    window.draw(scoreSprite3);
}

void Board::updateScore() {
    int flagged = 0;
    for (int i = 0; i < 16; i++) { // Might change
        for (int j = 0; j < 25; j++) {
            Tiles* current = tiles[i][j];
            if (current->getIsFlagged()) {
                flagged++;
            }
        }
    }

    int currentScore = bombs - flagged;
    score = to_string(currentScore) + "";
    char hundreds = score[0];
    if (hundreds == '-') {
        scoreSprite1.setTextureRect(IntRect(21 * 10, 0, 21, 32));
    }
    else {
        int first = hundreds - 48;
        scoreSprite1.setTextureRect(IntRect(21 * first, 0, 21, 32));
    }
    char tens = score[1];
    int second = tens - 48;
    scoreSprite2.setTextureRect(IntRect(21 * second, 0, 21, 32));
    char ones = score[2];
    int third = ones - 48;
    scoreSprite3.setTextureRect(IntRect(21 * third, 0, 21, 32));
}

void Board::addScore(int toAdd) {
    int currentScore = stoi(score);
    currentScore += toAdd;
    score = "" + to_string(currentScore);
}

void Board::generateBombs() {
    srand(time(nullptr));
    while (bombs < 50) {
        int i = rand() % 16; // Might change
        int j = rand() % 25; // Might change
        Tiles* tile = tiles[i][j];
        if (!tile->getIsMine()) {
            tile->createMine();
            setSprite(tile->getNextSprite(), bomb);
            bombs++;
            remainingTiles--;
        }
    }
}

void Board::setup() {
    isLost = false;
    isWon = false;
    remainingTiles = 400; // Might change
    setSprite(&faceSprite, happyFace);
    for (int i = 0; i < 16; i++) { // Might change
        for (int j = 0; j < 25; j++) { // Might change
            if (!tiles[i][j]) {
                delete tiles[i][j];
            }
            tiles[i][j] = new Tiles(hiddenTile, flag);
            tiles[i][j]->setpos(i * 32, j * 32);
        }
    }
    bombs = 0;
    generateBombs();
    setNeighbors();
}

void Board::loadFromFile(string fileName) {
    char x;
    fstream File(fileName, fstream::in);
    int i = 0;
    int j = 0;
    bombs = 0; // Might change
    remainingTiles = 400; // Might change

    while (File >> x) {
        Tiles* tile = tiles[i][j];
        setSprite(tile->getInitSprite(), hiddenTile);
        if (x == '0') {
            tile->setMine(false);
            tile->setShown(false);
            setSprite(tile->getNextSprite(), shownTile);
        }
        else if (x == '1') {
            tile->setMine(true);
            remainingTiles--;
            tile->setShown(false);
            bombs++;
            setSprite(tile->getNextSprite(), bomb);
        }
        j++;
        if (j > 24) {
            j = 0;
            i++;
        }
    }
    setNeighbors();
}

void Board::onClick(int x, int y, string clickType) {
    if (y > 512 && y < 578) {
        if (x >= (64 * 6) && x <= (64 * 7)) {
            setup();
        }
        else if (x >= (64 * 8) && x < (64 * 9) && !isLost && !isWon) {
            if (isDebug)
                isDebug = false;
            else {
                isDebug = true;
            }
        }
        else if (x >= (64 * 9) && x < (64 * 10) && !isLost && !isWon) {
            loadFromFile("../boards/testboard1.brd");
        }
        else if (x >= (64 * 10) && x < (64 * 11) && !isLost && !isWon) {
            loadFromFile("../boards/testboard2.brd");
        }
        else if (x >= (64 * 11) && x < (64 * 12) && !isLost && !isWon) {
            loadFromFile("../boards/testboard3.brd");
        }
    }
    else if (!isLost && !isWon) {
        int row = y / 32;
        int column = x / 32;
        Tiles* current = tiles[row][column];
        if (clickType == "left") {
            if (!current->getIsFlagged() && !current->getIsShown()) {
                onReveal(current);
            }
        }
        else if (clickType == "right") {
            toggleFlag(current);
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
    for (int i = 0; i < 16; i++) { // Might change
        for (int j = 0; j < 25; j++) { // Might change
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