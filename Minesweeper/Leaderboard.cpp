#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include "leaderboard.h"

int Leaderboard(int width, int height) {
    // Open the leaderboard file
    std::ifstream leaderboardFile("./files/leaderboard.txt");
    if (!leaderboardFile) {
        std::cerr << "Error opening leaderboard file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Read the leaderboard data and format it for display
    std::vector<std::string> leaderboardData;
    std::string line;
    int lineNumber = 1;
    while (std::getline(leaderboardFile, line)) {
        std::size_t separatorPos = line.find(",");
        std::string formattedLine = std::to_string(lineNumber) + ".\t" + line.substr(0, separatorPos) + "\t" + line.substr(separatorPos + 1);
        leaderboardData.push_back(formattedLine);
        ++lineNumber;
    }
    leaderboardFile.close();

    // Set up the window and font
    sf::RenderWindow window(sf::VideoMode(width, height), "Leaderboard");
    sf::Font font;
    if (!font.loadFromFile("./files/font.ttf")) {
        std::cerr << "Error opening font file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Set up the title text
    sf::Text titleText("LEADERBOARD", font, 20);
    titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleText.setFillColor(sf::Color::White);
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(width / 2, height / 2 - 120);

    // Set up the leaderboard text
    std::vector<sf::Text> leaderboardTexts;
    for (const std::string& formattedLine : leaderboardData) {
        sf::Text text(formattedLine, font, 18);
        text.setFillColor(sf::Color::White);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setPosition(width / 2, height / 2 - 100 + leaderboardTexts.size() * 50);
        leaderboardTexts.push_back(text);
    }

    // Run the window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Draw everything to the window
        window.clear(sf::Color::Blue);
        window.draw(titleText);
        for (const sf::Text& text : leaderboardTexts) {
            window.draw(text);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}