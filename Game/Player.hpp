#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void setPosition(int x, int y);
    void move(int dx, int dy);
    sf::Vector2i getPosition() const;

    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i position;
};

#endif // PLAYER_HPP
