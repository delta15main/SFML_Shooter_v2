#include <SFML/Graphics.hpp>
#include <cmath> 
#include <iostream>

#include "bullet.h"
#include "../utl/utils.h"

namespace blt {
    Bullet::Bullet(sf::Texture& texture, sf::Font& font) : Entity(texture, 1, false, font), direction({0.f, 0.f}), velocity(10.f) {
        sprite.setOrigin(sprite.getGlobalBounds().size / 2.f);
    }

    Hitbox Bullet::getHitbox() const {
        sf::Vector2f pos = sprite.getPosition();
        return Hitbox::makeCircle(pos, radius);
    }

    void Bullet::setAlive(bool b, const sf::Vector2f& playerPos) {
        if (b) {
            this->SPAWN(playerPos);
            health = 1;
            isAlive = true;
        } else {
            isAlive = false;
        }
    }

    void Bullet::setMousePos(sf::Vector2f mousepos) {
        mousePos = mousepos;
    }

    void Bullet::SPAWN(const sf::Vector2f& playerPos) {
        sf::Vector2f spawnPos = playerPos;
        spawnPos.x += 30.f;
        sprite.setPosition(spawnPos);
        position = sprite.getPosition();
        radius = sprite.getGlobalBounds().size.x / 2.f;
        this->update();
    }
    
    void Bullet::setDirection(sf::Vector2f dir) {
        direction = dir;
        float angleRad = std::atan2(dir.y, dir.x);
        sprite.setRotation(sf::radians(angleRad * 180.f / 3.14159f));
    }

    void Bullet::move(const sf::Vector2f& playerPos) {
        if (!isAlive) { return; }
        sf::Vector2f newPos = sprite.getPosition() + direction * velocity;
        
        if (newPos.x < 0.f || newPos.x > utl::get_max_size() || 
            newPos.y < 0.f || newPos.y > utl::get_max_size()) {
            isAlive = false;
            return;
        }
        
        sprite.setPosition(newPos);
        this->update();
    }

    void Bullet::update() {
        if (!isAlive) { return; }
        if (health <= 0) { 
            isAlive = false; 
            return;
        }
        position = sprite.getPosition();
        radius = sprite.getGlobalBounds().size.x / 2.f;
        healthText.update(sprite.getGlobalBounds(), std::to_string(health));
    } 

    void Bullet::draw(sf::RenderWindow& win) {
        win.draw(sprite);
        healthText.draw(win);
    }
}
