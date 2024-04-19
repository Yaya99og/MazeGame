#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

enum class MenuOption { None, Start, Exit };

class Menu {
public:
    Menu(sf::RenderWindow& window);

    MenuOption run();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text textStart;
    sf::Text textExit;
};

#endif // MENU_HPP
