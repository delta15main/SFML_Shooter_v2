#pragma once
#include <SFML/Graphics.hpp>

#include "../cor/hitbox.h"
#include "../res/res_manager.h"
#include "../cor/HUD.h"

class Entity {
protected:
    sf::Vector2f position, size;
    sf::Sprite sprite;
    HUD::HealthText healthText;
    float radius;
    int health;
    bool isAlive;

    void SETSPRITE() {
        sprite.setOrigin(sprite.getGlobalBounds().size / 2.f);
    }

public:
    // Base
    Entity(sf::Texture& texture, int heal, bool b, sf::Font& font) : sprite(texture), health(heal), isAlive(b), healthText(font) { 
        this->SETSPRITE(); 
    }
    virtual ~Entity() = default;
    // Get
    virtual Hitbox getHitbox() const = 0;
    virtual sf::Vector2f getPosition() const { return sprite.getPosition(); }
    bool IsAlive() const { return isAlive; }
    int getHealth() const { return health; }
    // Set
    virtual void setAlive(bool b, const sf::Vector2f& playerPos) { isAlive = b; }
    virtual void setHealth(int hp) { health = hp; }
    virtual void setPosition(const sf::Vector2f& pos) { sprite.setPosition(pos); }
    virtual void update() = 0;
    virtual void move(const sf::Vector2f& playerPos) = 0;
    // utils
    virtual void draw(sf::RenderWindow& win) { win.draw(sprite); }
};
