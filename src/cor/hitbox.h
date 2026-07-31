#pragma once
#include <SFML/Graphics.hpp>

struct Hitbox {
    sf::Vector2f position;
    float radius;
    sf::Vector2f size;

    static Hitbox makeCircle(const sf::Vector2f& center, float r) {
        return { center, r, {0, 0} };
    }

    static Hitbox makeAABB(const sf::Vector2f& topLeft, const sf::Vector2f& size) {
        return { topLeft, 0.0f, size };
    }

    bool intersects(const Hitbox& other) const {
        if (radius > 0 && other.radius > 0) {
            sf::Vector2f delta = position - other.position;
            float distSqr = delta.x * delta.x + delta.y * delta.y;
            float radSum = radius + other.radius;
            return distSqr < (radSum * radSum);
        }

        if (radius > 0 && other.radius == 0) {
            float closestX = std::max(other.position.x, std::min(position.x, other.position.x + other.size.x));
            float closestY = std::max(other.position.y, std::min(position.y, other.position.y + other.size.y));
            sf::Vector2f delta = position - sf::Vector2f(closestX, closestY);
            float distSqr = delta.x * delta.x + delta.y * delta.y;
            return distSqr < (radius * radius);
        }

        if (radius == 0 && other.radius > 0) {
            return other.intersects(*this);
        }

        return false;
    }
};
