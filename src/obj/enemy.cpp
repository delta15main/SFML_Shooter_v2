#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

#include "enemy.h"
#include "../utl/utils.h"

namespace enm {
    // Base
    Enemy::Enemy(sf::Texture& texture, sf::Font& font) : Entity(texture, 30, false, font), gen(rd()), velocity(0.3f) {
    sprite.setOrigin(sprite.getGlobalBounds().size / 2.f);
    position = sprite.getPosition();
    radius = sprite.getGlobalBounds().size.x / 2.f;
    }
    int Enemy::SPAWN(const sf::Vector2f& playerPos) {
        std::uniform_real_distribution<float> distP(50.f, utl::get_max_size() - 50.f);
        std::uniform_real_distribution<float> distSpeed(0.2f, 0.6f);
        velocity = distSpeed(gen);
        
        // Чем быстрее враг, тем меньше у него HP
        // Скорость 0.2 -> HP 40, скорость 0.6 -> HP 15
        health = 40 - int((velocity - 0.2f) / 0.4f * 25.f);
        if (health < 10) health = 10;
        if (health > 40) health = 40;
        
        for (int attempt = 0; attempt < 100; ++attempt) {
            sf::Vector2f newPos = {distP(gen), distP(gen)};
            sf::Vector2f diff = newPos - playerPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            if (dist > 200.f) {
                sprite.setPosition(newPos);
                position = sprite.getPosition();
                radius = sprite.getGlobalBounds().size.x / 2.f;
                return 1;
            }
        }
        sprite.setPosition({200.f, 200.f});
        position = sprite.getPosition();
        radius = sprite.getGlobalBounds().size.x / 2.f;
        return 1;
    }
    // Get
    Hitbox Enemy::getHitbox() const {
        sf::Vector2f pos = sprite.getPosition();
        return Hitbox::makeCircle(pos, radius);
    }
    // Set
    void Enemy::setAlive(bool b, const sf::Vector2f& playerPos) {
        if (!b) { 
            isAlive = false;
            return;
        }
        if (SPAWN(playerPos)) {
            isAlive = true;
        }
    }
    void Enemy::move(const sf::Vector2f& playerPos) {
        if ( !isAlive ) { return; }
        sprite.setPosition(this->SETPOSITION(playerPos));
        this->update();
    }
    sf::Vector2f Enemy::SETPOSITION(const sf::Vector2f& playerPos) {
        float dirX = playerPos.x - sprite.getPosition().x;
        float dirY = playerPos.y - sprite.getPosition().y;
        float len = std::sqrt(dirX * dirX + dirY * dirY);
        if (len > 0) {
            dirX /= len;
            dirY /= len;
        }
        float newX = sprite.getPosition().x + dirX * velocity;
        float newY = sprite.getPosition().y + dirY * velocity;
        return sf::Vector2f({newX, newY});
    }
    void Enemy::update() {
        if (health <= 0) { isAlive = false; }
        if (!isAlive) { return; }
        position = sprite.getPosition();
        radius = sprite.getGlobalBounds().size.x / 2.f;
        healthText.update(sprite.getGlobalBounds(), std::to_string(health));
    } 
    void Enemy::draw(sf::RenderWindow& win) {
        win.draw(sprite);
        healthText.draw(win);
    }
}
