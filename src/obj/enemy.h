#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#include "entity.h"
#include "../cor/hitbox.h"
#include "../utl/utils.h"

namespace  enm {
class Enemy : public Entity {
private:
    sf::Vector2i direction;
    float velocity;
    std::random_device rd;
    std::mt19937 gen;

    int SPAWN(const sf::Vector2f& playerPos);
    sf::Vector2f SETPOSITION(const sf::Vector2f& playerPos);

public:
    Enemy(sf::Texture& texture, sf::Font& font);
    // Get
    Hitbox getHitbox() const override;
    // Set
    void setAlive(bool b, const sf::Vector2f& playerPos) override;
    void move(const sf::Vector2f& playerPos) override;
    void update() override;
    void draw(sf::RenderWindow& win) override;
};
}
