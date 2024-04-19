#include "menu.hpp"

Menu::Menu(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("font/arial.ttf");

    textStart.setFont(font);
    textStart.setString("Start");
    textStart.setCharacterSize(24);
    textStart.setFillColor(sf::Color::White);
    textStart.setPosition(window.getSize().x / 2 - textStart.getGlobalBounds().width / 2,
        window.getSize().y / 2 - 50);

    textExit.setFont(font);
    textExit.setString("Exit");
    textExit.setCharacterSize(24);
    textExit.setFillColor(sf::Color::Red);
    textExit.setPosition(window.getSize().x / 2 - textExit.getGlobalBounds().width / 2,
        window.getSize().y / 2 + 50);
}

MenuOption Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (textStart.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    return MenuOption::Start;
                else if (textExit.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    return MenuOption::Exit;
            }
        }

        window.clear();
        window.draw(textStart);
        window.draw(textExit);
        window.display();
    }

    return MenuOption::None;
}
