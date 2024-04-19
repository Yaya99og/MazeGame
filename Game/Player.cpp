#include "Player.hpp"
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("images/coin.png")) {
        std::cerr << "Failed to load player image!" << std::endl;
        // Handle error...
    }
    sprite.setTexture(texture);
}

void Player::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(x * 40.f, y * 40.f); 
}

void Player::move(int dx, int dy) {
    position.x += dx;
    position.y += dy;
    sprite.setPosition(position.x * 40.f, position.y * 40.f); 
}

sf::Vector2i Player::getPosition() const {
    return position;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
