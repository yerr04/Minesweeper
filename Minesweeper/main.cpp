#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome to Minesweeper!");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("./files/font.ttf")) {
        std::cerr << "Error loading font file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Create welcome text
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    sf::FloatRect welcomeTextBounds = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextBounds.left + welcomeTextBounds.width / 2.0f,
        welcomeTextBounds.top + welcomeTextBounds.height / 2.0f);
    welcomeText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150);

    // Create input prompt text
    sf::Text inputPromptText("Enter your name:", font, 20);
    inputPromptText.setStyle(sf::Text::Bold);
    inputPromptText.setFillColor(sf::Color::White);
    sf::FloatRect inputPromptTextBounds = inputPromptText.getLocalBounds();
    inputPromptText.setOrigin(inputPromptTextBounds.left + inputPromptTextBounds.width / 2.0f,
        inputPromptTextBounds.top + inputPromptTextBounds.height / 2.0f);
    inputPromptText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 75);

    // Create input text
    sf::Text inputText("", font, 18);
    inputText.setStyle(sf::Text::Bold);
    inputText.setFillColor(sf::Color::Yellow);
    sf::FloatRect inputTextBounds = inputText.getLocalBounds();
    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
        inputTextBounds.top + inputTextBounds.height / 2.0f);
    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);

    // display "|" as a cursor to indicate where the next character will be entered
    sf::Text cursor("|", font, 18);
    cursor.setStyle(sf::Text::Bold);
    cursor.setFillColor(sf::Color::Yellow);
    sf::FloatRect cursorBounds = cursor.getLocalBounds();
    cursor.setOrigin(cursorBounds.left + cursorBounds.width / 2.0f,
        cursorBounds.top + cursorBounds.height / 2.0f);
    cursor.setPosition(window.getSize().x / 2.0f + inputTextBounds.width / 2.0f + 5, window.getSize().y / 2.0f - 45);

std::string playerName;
sf::Event event;

while (window.isOpen()) {
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { // backspace
                if (playerName.length() > 0) {
                    playerName.pop_back();
                    inputText.setString(playerName);
                    inputTextBounds = inputText.getLocalBounds();
                    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                        inputTextBounds.top + inputTextBounds.height / 2.0f);
                    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
                }
            }
            else if (event.text.unicode == 13) { // enter
                if (playerName.length() > 0) {
                    std::cout << playerName << std::endl;
                    window.close();
                }
            }
            else if (playerName.length() < 10 && isalpha(event.text.unicode)) { // only allow 10 characters
                playerName += static_cast<char>(event.text.unicode);
                inputText.setString(playerName);
                inputTextBounds = inputText.getLocalBounds();
                inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                    inputTextBounds.top + inputTextBounds.height / 2.0f);
                inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
            }
            // set the first character to uppercase
            if (playerName.length() > 0) {
                playerName[0] = toupper(playerName[0]);
                inputText.setString(playerName);
                inputTextBounds = inputText.getLocalBounds();
                inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                    inputTextBounds.top + inputTextBounds.height / 2.0f);
                inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
            }
            // sets all the other characters to lowercase
            for (int i = 1; i < playerName.length(); i++) {
                playerName[i] = tolower(playerName[i]);
                inputText.setString(playerName);
                inputTextBounds = inputText.getLocalBounds();
                inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                    inputTextBounds.top + inputTextBounds.height / 2.0f);
                inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
            }
        }
    }
    // Update cursor position
    cursor.setPosition(window.getSize().x / 2.0f + inputTextBounds.width / 2.0f + 5, window.getSize().y / 2.0f - 45);

    window.clear(sf::Color::Blue);
    window.draw(welcomeText);
    window.draw(inputPromptText);
    window.draw(cursor);
    window.draw(inputText);
    window.display();
}
window.close();

// create game window, but only if the player entered a name. If the player exits the window without entering a name, the game will not start
if (playerName.length() == 0) {
    return EXIT_FAILURE;
}
else {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Minesweeper");
    while (gameWindow.isOpen()) {
        // game stuff
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
    }
}
}