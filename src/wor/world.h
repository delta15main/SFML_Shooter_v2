#pragma once
#include <SFML/Graphics.hpp>

#include "../res/res_manager.h"
#include "../utl/utils.h"

namespace wor {
class World {
private:
    sf::Sprite sprite;

public:
    World(const sf::Texture& texture) : sprite(texture) {
        sprite.setOrigin({0.f, 0.f});
        sprite.setPosition({0.f, 0.f});
    }
    void draw(sf::RenderWindow& win) {
        win.draw(sprite);
    }

};
}
