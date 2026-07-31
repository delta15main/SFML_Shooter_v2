#pragma once
#include <SFML/Graphics.hpp>

#include "entity.h"
#include "../cor/hitbox.h"
#include "../utl/utils.h"

namespace plr {
class Player : public Entity {
private:
    sf::Vector2i direction;
    float velocity;
    int power;

public:
    Player(sf::Texture& texture, int heal, int pwr, sf::Font& font);
    // Get
    Hitbox getHitbox() const override;
    // Set
    void setDirection(sf::Vector2i& tmp);
    void move(const sf::Vector2f& playerPos) override;
    void update() override;
    void draw(sf::RenderWindow& win) override;
    
};
}
