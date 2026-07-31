#include <SFML/Graphics.hpp>
#include <iostream>

#include "../cor/hitbox.h"
#include "entity.h"
#include "player.h"
#include "../utl/utils.h"

namespace plr {
Player::Player(sf::Texture& texture, int heal, int pwr, sf::Font& font) : Entity(texture, heal, true, font), power(pwr), direction({0, 0}), velocity(0.3f) {
    sprite.setOrigin(sprite.getGlobalBounds().size / 2.f);
    position = sprite.getPosition();
    radius = sprite.getGlobalBounds().size.x / 2.f;
    sprite.setPosition({1000.f, 1000.f});
    }
    // Get
    Hitbox Player::getHitbox() const {
        sf::Vector2f pos = sprite.getPosition();
        return Hitbox::makeCircle(pos, radius);
    }
    // Set
    void Player::setDirection(sf::Vector2i& tmp) {
        direction = tmp;
    }
    void Player::move(const sf::Vector2f& playerPos) { 
        if (!isAlive || (!direction.x && !direction.y)) { return; }
        
        sf::Vector2f newPos;
        newPos.x = this->getPosition().x + direction.x * velocity;
        newPos.y = this->getPosition().y + direction.y * velocity;
        if (newPos.x >= utl::get_max_size() || newPos.y >= utl::get_max_size() || newPos.x <= 0.f || newPos.y <= 0.f) {
            return; 
        }

        sprite.setPosition(newPos);
        this->update();
    }
    void Player::update() {
        position = sprite.getPosition();
        radius = sprite.getGlobalBounds().size.x / 2.f;
        healthText.update(sprite.getGlobalBounds(), std::to_string(health));
    }
    void Player::draw(sf::RenderWindow& win) {
        win.draw(sprite);
        healthText.draw(win);
    }

}
