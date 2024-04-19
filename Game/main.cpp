#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include "Level.hpp"
#include "menu.hpp"
#include "Player.hpp"
#include "Time.hpp" 

int main() {
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Coin Escape");
    std::srand(std::sin(std::time(nullptr)) * 1000);
    int frameCount = 0;

    // Timer setup
    GameTimer timer(1);

    // Player setup
    Player player;
    player.setPosition(0, 1);

    // Level setup
    Level level;
    int currentLevel = 1;
    level.LevelSelect(currentLevel);
    int* gameMap = level.getLevelArray();

    // Font setup
    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    // Create menu
    Menu menu(window);
    MenuOption option = menu.run();

    switch (option) {
    case MenuOption::Start:
        // Start the game
        break;
    case MenuOption::Exit:
        window.close();
        break;
    default:
        break;
    }

    // Game loop
    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle player movement
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (player.getPosition().y > 0 && gameMap[player.getPosition().x + (player.getPosition().y - 1) * 20] != 1)
                        player.move(0, -1);
                    break;
                case sf::Keyboard::Down:
                    if (player.getPosition().y < 19 && gameMap[player.getPosition().x + (player.getPosition().y + 1) * 20] != 1)
                        player.move(0, 1);
                    break;
                case sf::Keyboard::Right:
                    if (player.getPosition().x < 19 && gameMap[(player.getPosition().x + 1) + player.getPosition().y * 20] != 1)
                        player.move(1, 0);
                    else if (player.getPosition().x == 19)
                    {
                        // If player collides with the right side of the screen
                        // Code to switch level 
                        currentLevel++;
                        level.LevelSelect(currentLevel);
                        gameMap = level.getLevelArray();
                        player.setPosition(0, 1);

                        // Display level completion message
                        sf::RectangleShape blackout(sf::Vector2f(window.getSize().x, window.getSize().y));
                        blackout.setFillColor(sf::Color::Black);
                        window.draw(blackout);

                        sf::Text levelCompletedText;
                        levelCompletedText.setFont(font);
                        levelCompletedText.setString("Congrats! New Level Unlocked: " + std::to_string(currentLevel) + "!!!");
                        levelCompletedText.setCharacterSize(30);
                        levelCompletedText.setFillColor(sf::Color::Green);
                        levelCompletedText.setPosition(200, 300);
                        window.draw(levelCompletedText);
                        window.display();
                        sf::sleep(sf::seconds(3)); // Display the message for 3 seconds

                        // Reset timer for the new level
                        timer.reset(1);
                    }
                    break;
                case sf::Keyboard::Left:
                    if (player.getPosition().x > 0 && gameMap[(player.getPosition().x - 1) + player.getPosition().y * 20] != 1)
                        player.move(-1, 0);
                    break;
                }
            }
        }

        // Check if time is up
        if (timer.isTimeUp()) {
            // Draw black rectangle to cover the entire window
            sf::RectangleShape blackout(sf::Vector2f(window.getSize().x, window.getSize().y));
            blackout.setFillColor(sf::Color::Black);
            window.draw(blackout);

            // Display time's up message
            sf::Text timeUpText;
            timeUpText.setFont(font);
            timeUpText.setString("Game Over! Try again. Time's Up.");
            timeUpText.setCharacterSize(30);
            timeUpText.setFillColor(sf::Color::Red);
            timeUpText.setPosition(200, 300);
            window.draw(timeUpText);

            // Display everything to window
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
            main();
        }

        // Draw everything
        window.clear(sf::Color::White);

        // Draw maze and player 
        sf::RectangleShape rect(sf::Vector2f(40.f, 40.f));
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                rect.setPosition(i * 40.f, j * 40.f);
                if (gameMap[i + j * 20] == 1) {
                    rect.setFillColor(sf::Color::Black); // Wall
                }
                else {
                    rect.setFillColor(sf::Color::White); // Path
                }
                window.draw(rect);
            }
        }
        player.draw(window); // Draw player

        // Display remaining time
        int remainingSeconds = timer.getRemainingSeconds();
        sf::Text timerText;
        timerText.setFont(font);
        timerText.setString("Time: " + std::to_string(remainingSeconds) + "s");
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::Red);
        timerText.setPosition(10, 10);
        window.draw(timerText);

        window.display(); // Display everything to window
    }

    return 0;
}
