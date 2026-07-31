#pragma once
#include <SFML/Graphics.hpp>

#include "entity.h"
#include "../cor/hitbox.h"

namespace blt {
class Bullet : public Entity {
private:
    sf::Vector2f direction;
    sf::Vector2f mousePos;
    float velocity;

    void SPAWN(const sf::Vector2f& playerPos);

public:
    Bullet(sf::Texture& texture, sf::Font& font);
    // Get
    Hitbox getHitbox() const override;
    // Set
    void setMousePos(sf::Vector2f mousepos);
    void setDirection(sf::Vector2f dir);
    void setAlive(bool b, const sf::Vector2f& playerPos) override;
    void move(const sf::Vector2f& playerPos) override;
    void update() override;
    void draw(sf::RenderWindow& win) override;
};
}
