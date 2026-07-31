#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

#include "../utl/utils.h"
#include "../cor/hitbox.h"
#include "../res/res_manager.h"
#include "../wor/world.h"
#include "../obj/enemy.h"
#include "../obj/bullet.h"
#include "../obj/player.h"

namespace gmr {
class Game {
private:
    sf::RenderWindow window;
    sf::View camera;
    sf::Vector2f playerPos;
    HUD::TextOnWindow healthText;
    HUD::ScoreText scoreText;
    res::Resourses resourses;
    wor::World world;
    plr::Player player;
    std::vector<std::shared_ptr<blt::Bullet>> bullets;
    std::vector<std::shared_ptr<enm::Enemy>> enemys;

    sf::Vector2f findNearestEnemy(const sf::Vector2f& playerPos);
    void spawnEnemies();

public:
    Game();
    void run();
    void update_all(sf::Vector2f& playerPos);
    void intersections(sf::Vector2f& playerPos, bool& isInvincible, sf::Clock& invincibilityClock);
};
}
